#include "mainwindow.h"
#include "ui_mainwindow.h"

// key size and IV
constexpr int KEY_SIZE = 32; // 256-byte key
constexpr int IV_SIZE = 16;  // 128-byte IV

// Fixed value of key and IV (ex. generate them manually and store them)
unsigned char key[KEY_SIZE] = {
    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
    0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10,
    0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
    0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20
};

unsigned char iv[IV_SIZE] = {
    0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28,
    0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30
};

MainWindow::MainWindow(const QString &dbAddress, const QString &dbName, const QString &username, const QString &password, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusbar->showMessage("ver. 1.2");

    // Connect to the database with the received parameters
    if (ConnectToDatabase(dbAddress, dbName, username, password, "1433"))
    {
        LoadUsers();        // loading the first table tab with users info
        LoadSettings();     // loading the second table tab with settings
        LoadServiceTree();  // loading the third table tab with service tree
    }
    else
    {
        QMessageBox::critical(this, "Помилка!", "Неможливо підключитися до бази даних.");
    }

    setWindowTitle("Properties-Recon");

    // Connect signals and sllots
    connect(ui->saveConfigButton, &QPushButton::clicked, this, &MainWindow::CreateConfigFile);                      // Config file creation button connector
    connect(ui->addUserButton, &QPushButton::clicked, this, &MainWindow::AddUserToDB);                              // Add User Button Connector
    connect(ui->userTableWidget, &QTableWidget::itemDoubleClicked, this, &MainWindow::UpdateUser);                  // User Parameters Update Button Connector
    connect(ui->deleteUserButton, &QPushButton::clicked, this, &MainWindow::DeleteUser);                            // User delete button connector
    connect(ui->settingsTableWidget, &QTableWidget::itemDoubleClicked, this, &MainWindow::OpenEditSettingsDialog);  // Settings Parameters Update Connector
    connect(ui->filledParamsCheck, &QCheckBox::checkStateChanged, this, &MainWindow::LoadServiceTree);              // Connector for connecting unfilled columns in the FTP table
    connect(ui->findUserEdit, &QLineEdit::textChanged, this, &MainWindow::FilterUsers);                             // textChanged connector from findUserEdit to filter function
    connect(ui->serviceTreeTableWidget, &QTableWidget::itemClicked, this, &MainWindow::OnFactorySelected);
    connect(ui->refreshFtpTableButton, &QPushButton::clicked, this, &MainWindow::LoadServiceTree);

}

// Connect to the database
bool MainWindow::ConnectToDatabase(const QString &dbAddress, const QString &databaseName, const QString &username, const QString &password, const QString &instanceOrPort)
{
    DBConnection = QSqlDatabase::addDatabase("QODBC");

    QString serverAddress;
    // Check if port/instance is specified
    if (!instanceOrPort.isEmpty()) {
        // If a numeric port is specified, add it to the address
        bool isPort = instanceOrPort.toInt() > 0;
        if (isPort) {
            serverAddress = QString("%1,%2").arg(dbAddress, instanceOrPort);
        } else {
            // Otherwise, add the instance name
            serverAddress = QString("%1\\%2").arg(dbAddress, instanceOrPort);
        }
    } else {
        // If no port/instance is specified, we use only the address
        serverAddress = dbAddress;
    }

    QString dsn = QString("Driver={SQL Server};Server=%1;Database=%2;UID=%3;PWD=%4;Encrypt=no;TrustServerCertificate=yes;")
                      .arg(serverAddress, databaseName, username, password);
    DBConnection.setDatabaseName(dsn);

    if (!DBConnection.open()) {
        QMessageBox::critical(this, "Fatal Error!",
                              DBConnection.lastError().text() +
                                  "\nServer Name: " + serverAddress +
                                  "\nDatabase Name: " + databaseName);
        return false;
    }

    return true;
}

// Disconnecting from the database
void MainWindow::DisconnectFromDatabase()
{
    if (DBConnection.isOpen())
    {
        DBConnection.close();
    }
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);  // Remove connection
}

// Method for loading application settings (also called when the program is launched)
void MainWindow::LoadSettings()
{
    // Resetting the table: clearing data
    ui->settingsTableWidget->clear();

    // Set the number of rows and columns
    ui->settingsTableWidget->setRowCount(0);
    ui->settingsTableWidget->setColumnCount(3);
    ui->settingsTableWidget->setHorizontalHeaderLabels(QStringList() << "Коментар" << "Значення" << "Ім'я");

    // Querying data from a joined table
    QSqlQuery query("SELECT [value], [comment], [name], [mu] FROM [ReconDB].[dbo].[access_settings];");

    while (query.next())
    {
        int row = ui->settingsTableWidget->rowCount();
        ui->settingsTableWidget->insertRow(row);

        QString value = query.value(0).toString() + query.value(3).toString();
        QString comment = query.value(1).toString();
        QString name = query.value(2).toString();

        QTableWidgetItem *nameItem = new QTableWidgetItem(name);
        nameItem->setFlags(nameItem->flags() & ~Qt::ItemIsEditable);
        ui->settingsTableWidget->setItem(row, 2, nameItem);
        ui->settingsTableWidget->setColumnHidden(2, true);

        QTableWidgetItem *valueItem = nullptr;

        // Processing JSON values
        if (name == "database" || name == "mail" || name == "onedrive" || name == "file_integration")
        {
            QJsonDocument jsonDoc = QJsonDocument::fromJson(value.toUtf8());
            if (!jsonDoc.isNull() && jsonDoc.isObject())
            {
                QJsonObject jsonObj = jsonDoc.object();
                QString formattedValue;

                if (name == "database")
                {
                    formattedValue = QString::asprintf("Адреса БД: %s\n\nІм'я БД: %s\n\nЛогін: %s\n\nПароль: %s",
                                                       jsonObj["addressDB"].toString().toUtf8().constData(),
                                                       jsonObj["nameDB"].toString().toUtf8().constData(),
                                                       jsonObj["login"].toString().toUtf8().constData(),
                                                       jsonObj["password"].toString().toUtf8().constData());

                    valueItem = new QTableWidgetItem(formattedValue);

                    valueItem->setFlags(valueItem->flags() & ~(Qt::ItemIsSelectable | Qt::ItemIsEnabled));
                }
                else if (name == "mail")
                {
                    formattedValue = QString::asprintf("SMTP Сервер: %s\n\nEmail відправника: %s\n\nІм'я відправника: %s\n\nПорт: %s\n\nШаблон повідомлення: %s\n\nSSL: %s\n\nАутентифікація: %s",
                                                       jsonObj["SMTP server"].toString().toUtf8().constData(),
                                                       jsonObj["email_sender"].toString().toUtf8().constData(),
                                                       jsonObj["name_sender"].toString().toUtf8().constData(),
                                                       jsonObj["port"].toString().toUtf8().constData(),
                                                       jsonObj["msg_template"].toString().toUtf8().constData(),
                                                       jsonObj["ssl"].toBool() ? "Так" : "Ні",
                                                       jsonObj["auth"].toBool() ? "Так" : "Ні");

                    valueItem = new QTableWidgetItem(formattedValue);
                }
                else if (name == "onedrive")
                {
                    formattedValue = QString("Шлях до папки: %1\n\nТермін зберігання (міс.): %2")
                                         .arg(jsonObj["path"].toString())
                                         .arg(jsonObj["months"].toInt());

                    valueItem = new QTableWidgetItem(formattedValue);
                }
                else if(name == "file_integration"){
                    formattedValue = QString::asprintf("Інтеграція в БД - вкл/вимк: %s\n\nЗбір по FTP - вкл/вимк: %s\n\nРозсилка пошти - вкл/вимк: %s\n\nOneDrive - вкл/вимк: %s\n\n База заповнена: %s",
                                         jsonObj["integrationIsActive"].toBool() ? "Так" : "Ні",
                                         jsonObj["ftpIsActive"].toBool() ? "Так" : "Ні",
                                         jsonObj["mailIsActive"].toBool() ? "Так" : "Ні",
                                         jsonObj["oneDriveIsActive"].toBool() ? "Так" : "Ні",
                                         jsonObj["dbIsFull"].toBool() ? "Так" : "Ні");

                    valueItem = new QTableWidgetItem(formattedValue);
                    valueItem->setFlags(valueItem->flags() & ~(Qt::ItemIsSelectable | Qt::ItemIsEnabled));
                }

                if (valueItem)
                {
                    valueItem->setFlags(valueItem->flags() & ~Qt::ItemIsEditable);
                    ui->settingsTableWidget->setItem(row, 1, valueItem);
                }
            }
        }
        else if(name == "groups"){
            QCheckBox *checkBox = new QCheckBox("Увімкнено", this);
            checkBox->setChecked(value == "1");
            checkBox->setProperty("row", row);

            connect(checkBox, &QCheckBox::toggled, this, &MainWindow::updateGroupSetting);

            ui->settingsTableWidget->setCellWidget(row, 1, checkBox);
        }
        else
        {
            valueItem = new QTableWidgetItem(value);
            valueItem->setFlags(valueItem->flags() & ~Qt::ItemIsEditable);
            ui->settingsTableWidget->setItem(row, 1, valueItem);
        }

        QTableWidgetItem *commentItem = new QTableWidgetItem(comment);
        commentItem->setFlags(commentItem->flags() & ~Qt::ItemIsEditable);
        ui->settingsTableWidget->setItem(row, 0, commentItem);

        if (name == "database")
        {
            commentItem->setFlags(commentItem->flags() & ~(Qt::ItemIsSelectable | Qt::ItemIsEnabled));
            nameItem->setFlags(nameItem->flags() & ~(Qt::ItemIsSelectable | Qt::ItemIsEnabled));
        }
    }

    ui->settingsTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->settingsTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->settingsTableWidget->verticalHeader()->setVisible(false);

    ui->settingsTableWidget->resizeRowsToContents();
    ui->settingsTableWidget->horizontalHeader()->setStretchLastSection(true);
}

void MainWindow::updateGroupSetting(bool checked)
{
    // Определяем строку из свойства чекбокса
    QCheckBox *checkBox = qobject_cast<QCheckBox *>(sender());
    if (!checkBox) return;

    int row = checkBox->property("row").toInt();

    // Получаем имя из третьего столбца (скрытого)
    QTableWidgetItem *nameItem = ui->settingsTableWidget->item(row, 2);
    if (!nameItem) return;

    QString name = nameItem->text();

    // Обновляем значение в базе данных
    QSqlQuery query;
    query.prepare("UPDATE [ReconDB].[dbo].[access_settings] SET [value] = :value WHERE [name] = :name");
    query.bindValue(":value", checked ? "1" : "0");
    query.bindValue(":name", name);

    if (!query.exec())
    {
        QMessageBox::critical(this, "Ошибка", "Не удалось обновить значение: " + query.lastError().text());
        return;
    }

    qDebug() << "Значение обновлено: " << name << " -> " << (checked ? "1" : "0");
}


// Метод для обновления данных о параметрах в БД
void MainWindow::OpenEditSettingsDialog()
{
    int currentRow = ui->settingsTableWidget->currentRow();
    QString name = ui->settingsTableWidget->item(currentRow, 2)->text();
    QString value = ui->settingsTableWidget->item(currentRow, 1)->text();

    // Создание диалогового окна
    QDialog *dialog = createDialog(name, value);
    dialog->exec();
    delete dialog;
}

// Создание диалогового окна для айпи
QDialog* MainWindow::createDialog(const QString &name, QString &value)
{
    QDialog *dialog = new QDialog(this);
    QVBoxLayout *layout = new QVBoxLayout(dialog);
    QPushButton *saveButton = new QPushButton("Зберегти", dialog);

    if (name == "mail") {
        setupMailSettings(layout, value, saveButton);
    } else if (name == "onedrive") {
        setupOnedriveSettings(layout, value);
    } else if (name == "root_directory") {
        setupRootDirectorySettings(layout, value);
    } else {
        setupDefaultSettings(layout, value);
    }

    layout->addWidget(saveButton);
    connect(saveButton, &QPushButton::clicked, [this, name, dialog]() {
        if (saveSettings(name)) {
            dialog->accept();   // Закрыть диалог, если сохранение успешно
            LoadSettings();     // Обновить таблицу
        }
    });

    return dialog;
}

// Установка параметров для почтового сервера в диалоговое окно
void MainWindow::setupMailSettings(QVBoxLayout *layout, const QString &value, QPushButton *saveButton)
{
    smtpEdit = new QLineEdit();                              // Поле для ввода SMTP сервера
    emailSenderEdit = new QLineEdit();                       // Поле для ввода почты отправителя
    nameSenderEdit = new QLineEdit();                        // Поле для ввода имени отправителя
    portEdit = new QLineEdit();                              // Поле для ввода порта сервера

    msgTemplate = new QTextEdit();                           // Поле для ввода шаблона сообщения
    sslCheck = new QCheckBox("Використовувати SSL");         // Галочка для включения SSL
    authCheck = new QCheckBox("Викорис. Аутентифікацію");    // Галочка для включения Аунтефикации
    authLoginEdit = new QLineEdit();                         // Поле для ввода Логина в случае Аунтефикации
    authPasswordEdit = new QLineEdit();                      // Поле для ввода Пароля в случае Аунтефикации

    msgTemplate->setText("Привіт, ви отримали файли.");     // Текст по умолчанию
    msgTemplate->setReadOnly(false);                        // Разрешение на редактировани

    // Установка значений из JSON-объекта или форматированной строки
    QJsonDocument jsonDoc = QJsonDocument::fromJson(value.toUtf8());
    if (!jsonDoc.isNull() && jsonDoc.isObject()) {
        QJsonObject jsonObj = jsonDoc.object();
        smtpEdit->setText(jsonObj["SMTP server"].toString());
        emailSenderEdit->setText(jsonObj["email_sender"].toString());
        nameSenderEdit->setText(jsonObj["name_sender"].toString());
        portEdit->setText(jsonObj["port"].toString());
        msgTemplate->setText(jsonObj["msg_template"].toString());
        sslCheck->setChecked(jsonObj["ssl"].toBool());
        authCheck->setChecked(jsonObj["auth"].toBool());
        authLoginEdit->setText(jsonObj["login"].toString());
        authPasswordEdit->setText(jsonObj["password"].toString());
    } else {
        // Парсинг форматированной строки
        static const QRegularExpression smtpRegex("SMTP Сервер: (.*)");
        static const QRegularExpression emailRegex("Email відправника: (.*)");
        static const QRegularExpression nameRegex("Ім'я відправника: (.*)");
        static const QRegularExpression portRegex("Порт: (.*)");
        static const QRegularExpression msgRegex("Шаблон повідомлення: (.*)");
        static const QRegularExpression sslRegex("SSL: (Так|Ні)");
        static const QRegularExpression authRegex("Аутентифікація: (Так|Ні)");

        // Использование статических объектов QRegularExpression для парсинга
        QRegularExpressionMatch match;

        match = smtpRegex.match(value);
        if (match.hasMatch()) {
            smtpEdit->setText(match.captured(1).trimmed());
        }
        match = emailRegex.match(value);
        if (match.hasMatch()) {
            emailSenderEdit->setText(match.captured(1).trimmed());
        }
        match = nameRegex.match(value);
        if (match.hasMatch()) {
            nameSenderEdit->setText(match.captured(1).trimmed());
        }
        match = portRegex.match(value);
        if (match.hasMatch()) {
            portEdit->setText(match.captured(1).trimmed());
        }
        match = msgRegex.match(value);
        if (match.hasMatch()) {
            msgTemplate->setText(match.captured(1).trimmed());
        }
        match = sslRegex.match(value);
        if (match.hasMatch()) {
            sslCheck->setChecked(match.captured(1).trimmed() == "Так");
        }
        match = authRegex.match(value);
        if (match.hasMatch()) {
            authCheck->setChecked(match.captured(1).trimmed() == "Так");
        }

        // Добавление полей в диалоговое окно настройки
        layout->addWidget(new QLabel("SMTP Сервер:"));
        layout->addWidget(smtpEdit);
        layout->addWidget(new QLabel("Email відправника:"));
        layout->addWidget(emailSenderEdit);
        layout->addWidget(new QLabel("Ім'я відправника:"));
        layout->addWidget(nameSenderEdit);
        layout->addWidget(new QLabel("Порт:"));
        layout->addWidget(portEdit);
        layout->addWidget(new QLabel("Шаблон повідомлення:"));
        layout->addWidget(msgTemplate);
        layout->addWidget(sslCheck);
        layout->addWidget(authCheck);

        // Подключение коннектора для включение доступа к вводу параметров логина и пароля
        connect(authCheck, &QCheckBox::toggled, [=](bool checked)
                {
                    layout->removeWidget(saveButton);

                    QLabel *loginLabel = new QLabel("Логін:");                      // Лейбл для логина в случае Аунтефикации
                    QLabel *passwordLabel = new QLabel("Пароль:");                  // Лейбл для пароля в случае Аунтефикации

                    if(checked)
                    {
                        // Если галочка активирована, добавляем поля логина и пароля
                        layout->addWidget(loginLabel);
                        layout->addWidget(authLoginEdit);
                        layout->addWidget(passwordLabel);
                        layout->addWidget(authPasswordEdit);

                        // Делаем видимыми поля логина и пароля
                        loginLabel->setVisible(true);
                        authLoginEdit->setVisible(true);
                        passwordLabel->setVisible(true);
                        authPasswordEdit->setVisible(true);
                    }
                    else
                    {
                        // Если галочка снята удаляем поле ввода логина и пароля
                        layout->removeWidget(loginLabel);
                        layout->removeWidget(authLoginEdit);
                        layout->removeWidget(passwordLabel);
                        layout->removeWidget(authPasswordEdit);

                        // Удаляем их из видимости
                        loginLabel->setVisible(false);
                        authLoginEdit->setVisible(false);
                        passwordLabel->setVisible(false);
                        authPasswordEdit->setVisible(false);
                    }
                    layout->addWidget(saveButton);
                });
    }
}

// Установка параметров для Onedrive в диалоговое окно
void MainWindow::setupOnedriveSettings(QVBoxLayout *layout, const QString &value)
{
    // Регулярные выражения для парсинга значений JSON
    static const QRegularExpression pathRegex("Шлях до папки:\\s*([^\\n]*)");
    static const QRegularExpression monthsRegex("Термін зберігання \\(міс\\.\\):\\s*(\\d+)");

    pathEdit = new QLineEdit();
    monthsEdit = new QLineEdit();

    // Горизонтальный layout для кнопки и поля ввода
    QHBoxLayout *pathLayout = new QHBoxLayout;

    // Кнопка для открытия диалога выбора папки
    QPushButton *browseButton = new QPushButton("...");

    connect(browseButton, &QPushButton::clicked, [this]()
            {
                QString dirPath = QFileDialog::getExistingDirectory(this, "Оберіть папку");
                if (!dirPath.isEmpty())
                {
                    pathEdit->setText(dirPath);  // Устанавливаем выбранный путь в поле ввода
                }
            });

    // Добавление кнопки и поля ввода в горизонтальный layout
    pathLayout->addWidget(pathEdit);
    pathLayout->addWidget(browseButton);

    // Установка значений из JSON-объекта
    QRegularExpressionMatch match;

    // Проверяем путь
    match = pathRegex.match(value);
    if (match.hasMatch()) {
        QString capturedPath = match.captured(1).trimmed();
        pathEdit->setText(capturedPath);
    }

    // Проверяем срок хранения
    match = monthsRegex.match(value);
    if (match.hasMatch()) {
        QString capturedMonths = match.captured(1).trimmed();
        monthsEdit->setText(capturedMonths);
    }

    layout->addWidget(new QLabel("Шлях до папки:"));
    layout->addLayout(pathLayout);
    layout->addWidget(new QLabel("Термін зберігання (міс.):"));
    layout->addWidget(monthsEdit);
}

// Установка параметров для корневой директории в диалоговое окно
void MainWindow::setupRootDirectorySettings(QVBoxLayout *layout, const QString &value)
{
    rootPathEdit = new QLineEdit();
    rootPathEdit->setText(value);

    QHBoxLayout *pathLayout = new QHBoxLayout();
    QPushButton *browseButton = new QPushButton("...");
    pathLayout->addWidget(rootPathEdit);
    pathLayout->addWidget(browseButton);

    connect(browseButton, &QPushButton::clicked, [this]()
    {
        QString dirPath = QFileDialog::getExistingDirectory(this, "Оберіть папку");
        if (!dirPath.isEmpty())
        {
            rootPathEdit->setText(dirPath);
        }
    });

    layout->addWidget(new QLabel("Шлях до папки:"));
    layout->addLayout(pathLayout);
}

// Установка параметров для остальных значений в диалоговое окно
void MainWindow::setupDefaultSettings(QVBoxLayout *layout, QString &value)
{
    timeValueEdit = new QLineEdit();
    value.chop(1);
    timeValueEdit->setText(value);

    layout->addWidget(new QLabel("Значення:"));
    layout->addWidget(timeValueEdit);
}

// Функция сохранения введённых параметров через кнопку сохранения
bool MainWindow::saveSettings(const QString &name)
{
    QJsonObject json;
    QSqlQuery query;
    bool success = false;

    if (name == "mail")
    {
        // Создание JSON строки для mail
        QJsonObject json;
        json["SMTP server"] = smtpEdit->text();
        json["email_sender"] = emailSenderEdit->text();
        json["name_sender"] = nameSenderEdit->text();
        json["port"] = portEdit->text();
        bool isValid = true;  // Предполагаем, что ввод корректен

        for (int var = 0; var < portEdit->text().length(); ++var) {
            if (!portEdit->text().at(var).isDigit()) {
                isValid = false;
                break;  // Если встречен нецифровой символ, выходим из цикла
            }
        }

        if (!isValid) {
            portEdit->setStyleSheet("border: 1px solid red;");
            return success;
        } else {
            portEdit->setStyleSheet("");  // Если всё в порядке, можно сбросить стиль
        }
        json["msg_template"] = msgTemplate->toPlainText();
        json["ssl"] = sslCheck->isChecked();
        json["auth"] = authCheck->isChecked();
        if (authCheck->isChecked())
        {
            json["login"] = authLoginEdit->text();
            json["password"] = authPasswordEdit->text();
        }
        QJsonDocument doc(json);
        QString jsonString = QString::fromUtf8(doc.toJson());


        query.prepare("UPDATE [ReconDB].[dbo].[access_settings] SET [value] = :value WHERE [name] = :name");
        query.bindValue(":value", jsonString);
        query.bindValue(":name", name);
        success = query.exec();
    }
    else if (name == "onedrive")
    {
        // Проверка, что введено целое число в диапазоне от 1 до 4
        bool ok;
        int monthCount = monthsEdit->text().toInt(&ok);

        if (!ok || monthCount < 1 || monthCount > 36)
        {
            QMessageBox::critical(this, "Помилка", "Значення '" + monthsEdit->text() + "' некоректне. Введіть ціле число від 1 до 36.");
            return false;
        }

        // Создание JSON строки для onedrive
        QJsonObject json;
        json["path"] = pathEdit->text();
        json["months"] = monthCount;
        QJsonDocument doc(json);
        QString jsonString = QString::fromUtf8(doc.toJson());

        query.prepare("UPDATE [ReconDB].[dbo].[access_settings] SET [value] = :value WHERE [name] = :name");
        query.bindValue(":value", jsonString);
        query.bindValue(":name", name);
        success = query.exec();
    }
    else if(name == "root_directory")
    {
        query.prepare("UPDATE [ReconDB].[dbo].[access_settings] SET [value] = :value WHERE [name] = :name");
        query.bindValue(":value", rootPathEdit->text());
        query.bindValue(":name", name);
        success = query.exec();
    }
    else
    {
        bool ok;
        int timeValue = timeValueEdit->text().toInt(&ok);

        if (!ok || timeValue < 1 || timeValue > 3600)
        {
            QMessageBox::critical(this, "Помилка", "Значення '" + timeValueEdit->text() + "' некоректне. Введіть ціле число від 10 до 60.");
            return false; // Завершаем выполнение, если значение некорректно
        }

        query.prepare("UPDATE [ReconDB].[dbo].[access_settings] SET [value] = :value, [mu] = :mu WHERE [name] = :name");
        query.bindValue(":value", timeValue);
        query.bindValue(":mu", "s");
        query.bindValue(":name", name);
        success = query.exec();
    }
    return success;
}

// Создания конфиг файла (сделать под новую структуру бд) p.s. можно пока что не шифровать
void MainWindow::CreateConfigFile()
{
    // Retrieve data from database
    QSqlQuery query;
    query.prepare("SELECT [value] FROM [ReconDB].[dbo].[access_settings] WHERE [name] = 'database'");

    if (!query.exec() || !query.next())
    {
        QMessageBox::critical(this, "Помилка", "Не вдалося отримати параметри бази даних: " + query.lastError().text());
        return;
    }

    // Get the JSON string from the database
    QString jsonString = query.value(0).toString();

    // Parse JSON to retrieve server, login, and password
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());
    if (jsonDoc.isNull() || !jsonDoc.isObject())
    {
        QMessageBox::critical(this, "Помилка", "Invalid JSON format: " + jsonString);
        return;
    }

    QJsonObject jsonObj = jsonDoc.object();
    QString serverName = jsonObj["addressDB"].toString();
    QString dbName = jsonObj["nameDB"].toString();
    QString dbUsername = jsonObj["login"].toString();
    QString dbPassword = jsonObj["password"].toString();

    // Формируем данные для записи
    QByteArray configData;
    configData.append("server=" + serverName.toUtf8() + '\n');
    configData.append("database=" + dbName.toUtf8() + '\n');
    configData.append("username=" + dbUsername.toUtf8() + '\n');
    configData.append("password=" + dbPassword.toUtf8() + '\n');

    // Open file dialog to select the save location
    QString filePath = QFileDialog::getSaveFileName(this, "Save Config File", "", "Config Files (*.conf)");
    if (filePath.isEmpty())
    {
        return; // User cancelled the dialog
    }

    // Open file for binary writing
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        QMessageBox::critical(this, "Помилка", "Неможливо відкрити файл для запису");
        return;
    }

    if (encryptDataToFile(configData, filePath, key, iv)) {
        QMessageBox::information(this, "Успішно", "Файл конфігурації успішно створено та зашифровано!");
    } else {
        QMessageBox::critical(this, "Помилка", "Не вдалося зашифрувати файл.");
    }
}

bool MainWindow::encryptDataToFile(const QByteArray& data, const QString& filePath, const unsigned char* key, const unsigned char* iv) {
    QFile outputFile(filePath);
    if (!outputFile.open(QIODevice::WriteOnly)) {
        return false;
    }

    // Записываем IV в начало файла
    outputFile.write(reinterpret_cast<const char*>(iv), IV_SIZE);

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        return false;
    }

    if (EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    QByteArray encryptedBuffer;
    int outLen = 0;

    // Шифруем данные
    encryptedBuffer.resize(data.size() + EVP_CIPHER_block_size(EVP_aes_256_cbc()));
    if (EVP_EncryptUpdate(ctx, reinterpret_cast<unsigned char*>(encryptedBuffer.data()), &outLen,
                          reinterpret_cast<const unsigned char*>(data.data()), data.size()) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }
    outputFile.write(encryptedBuffer.data(), outLen);

    // Завершаем шифрование
    if (EVP_EncryptFinal_ex(ctx, reinterpret_cast<unsigned char*>(encryptedBuffer.data()), &outLen) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }
    outputFile.write(encryptedBuffer.data(), outLen);

    EVP_CIPHER_CTX_free(ctx);
    outputFile.close();

    return true;
}

// Метод фильтрации пользователей
void MainWindow::FilterUsers(const QString &searchText)
{
    for (int row = 0; row < ui->userTableWidget->rowCount(); ++row)
    {
        bool match = false;

        // Получаем текст из столбца логина (столбец 0)
        QTableWidgetItem *loginItem = ui->userTableWidget->item(row, 0);
        if (loginItem)
        {
            QString loginText = loginItem->text();

            // Проверяем, соответствует ли логин введенному тексту
            if (loginText.startsWith(searchText, Qt::CaseInsensitive))
            {
                match = true;
            }
        }

        // Скрываем строку, если она не подходит под фильтр
        ui->userTableWidget->setRowHidden(row, !match);
    }
}

// Метод загрузки пользователей (вызывается так же при запуске программы)
void MainWindow::LoadUsers()
{
    ui->userTableWidget->clear();

    // Установите количество строк и столбцов
    ui->userTableWidget->setRowCount(0);
    ui->userTableWidget->setColumnCount(8);
    ui->userTableWidget->setHorizontalHeaderLabels(QStringList() << "Логін" << "Тип" << "Об'єкти"
                                                                 << "Розсилка даних" << "Шлях до WinRec"
                                                                 << "Посада користувача"
                                                                 << "Зміна пароля користувачу"
                                                                 << "Статус(Активний / Не активний)");

    // Запрос данных из таблицы users
    QSqlQuery query1("SELECT U.[id], U.[login], U.[type], U.[send_mail], U.[winrec_path], U.[post] ,U.[status], "
                     "STUFF((SELECT CHAR(10) + UN.[unit] + '. ' + UN.[substation] "
                     "FROM [ReconDB].[dbo].[users_units] UU "
                     "JOIN [ReconDB].[dbo].[units] UN ON UU.[unit_id] = UN.[id] "
                     "WHERE UU.[user_id] = U.[id] FOR XML PATH('')), 1, 1, '') AS [Об'єкти] "
                     "FROM [ReconDB].[dbo].[users] U");

    while (query1.next())
    {
        int row = ui->userTableWidget->rowCount();
        ui->userTableWidget->insertRow(row);

        // Получаем userID для текущей строки
        int userID = query1.value(0).toInt();

        // Заполняем данные из таблицы Users
        QTableWidgetItem *loginItem = new QTableWidgetItem(query1.value(1).toString());
        loginItem->setFlags(loginItem->flags() & ~Qt::ItemIsEditable);
        ui->userTableWidget->setItem(row, 0, loginItem);

        QTableWidgetItem *typeItem = new QTableWidgetItem(query1.value(2).toString());
        typeItem->setFlags(typeItem->flags() & ~Qt::ItemIsEditable);
        ui->userTableWidget->setItem(row, 1, typeItem);

        // Разбиваем объекты на отдельные строки
        QString objectsList = query1.value(7).toString();
        QStringList objects = objectsList.split("\n", Qt::SkipEmptyParts);

        // Если есть объекты, показываем первый объект
        if (!objects.isEmpty() && typeItem->text() != "Адмін")
        {
            // Создаем QComboBox для объектов
            QComboBox *objectsComboBox = new QComboBox();
            objectsComboBox->addItem(objects.first());

            // Добавляем остальные объекты в выпадающий список
            if (objects.size() > 1)
            {
                objectsComboBox->addItems(objects.mid(1));
            }

            // Устанавливаем ComboBox в нужную ячейку
            ui->userTableWidget->setCellWidget(row, 2, objectsComboBox);
        }
        else if(typeItem->text() == "Адмін"){
            QTableWidgetItem *objectsItem = new QTableWidgetItem("Всі об'єкти");
            ui->userTableWidget->setItem(row, 2, objectsItem);
        }

        QString sendMailStatus = query1.value(3).toInt() == 1 ? "так" : "ні";
        QTableWidgetItem *statusItem = new QTableWidgetItem(sendMailStatus);
        statusItem->setFlags(statusItem->flags() & ~Qt::ItemIsEditable);
        ui->userTableWidget->setItem(row, 3, statusItem);

        QTableWidgetItem *winRecItem = new QTableWidgetItem(query1.value(4).toString());
        winRecItem->setFlags(winRecItem->flags() & ~Qt::ItemIsEditable);
        ui->userTableWidget->setItem(row, 4, winRecItem);

        QTableWidgetItem *userWorkPosition= new QTableWidgetItem(query1.value(5).toString());
        userWorkPosition->setFlags(userWorkPosition->flags() & ~Qt::ItemIsEditable);
        ui->userTableWidget->setItem(row, 5, userWorkPosition);

        // Проверяем тип пользователя и закрашиваем строку в жёлтый цвет, если это "Адмін"
        if (typeItem->text() == "Адмін")
        {
            for (int col = 0; col <= 5; ++col)
            {
                ui->userTableWidget->item(row, col)->setBackground(QBrush(Qt::yellow));
            }
        }

        // Кнопка для смены пароля
        QPushButton *changePasswordButton = new QPushButton("Змінити пароль");
        ui->userTableWidget->setCellWidget(row, 6, changePasswordButton);

        // Чекбокс(галочка) для активности пользователя
        QCheckBox *isActiveUser = new QCheckBox();
        isActiveUser->setChecked(query1.value(6).toBool());
        ui->userTableWidget->setCellWidget(row, 7, isActiveUser);

        // Сигнал изменения состояния чекбокса к функции обновления статуса
        connect(isActiveUser, &QCheckBox::checkStateChanged, [this, userID](int state)
        {
            UpdateUserStatus(userID, state == Qt::Checked);
        });

        // Проверяем статус юзера и закрашиваем строку в серый цвет, если он "неактивный"
        if (isActiveUser->isChecked() == false)
        {
            for (int col = 0; col <= 1; ++col)
            {
                ui->userTableWidget->item(row, col)->setBackground(QBrush(Qt::lightGray));
            }
        }

        // Сигнал нажатия кнопки изменения пароля к функции изменения пароля
        connect(changePasswordButton, &QPushButton::clicked, this, [=]()
        {
            HandleChangePassword(userID);
        });

        for (int col = 0; col < ui->userTableWidget->columnCount(); ++col)
        {
            QTableWidgetItem *item = ui->userTableWidget->item(row, col);
            if (item)
            {
                QString text = item->text().replace("<br>", "\n");
                item->setText(text);
            }
        }
    }

    // Отключение редактирования таблицы, но включение выделения строк
    ui->userTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->userTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->userTableWidget->verticalHeader()->setVisible(false);

    ui->userTableWidget->resizeColumnsToContents();
    ui->userTableWidget->resizeRowsToContents();
    ui->userTableWidget->horizontalHeader()->setStretchLastSection(true);
}

// Метод для создания диалога пользователя
QDialog* MainWindow::CreateUserDialog(QLineEdit*& userLoginEdit, QLineEdit*& userWorkPositionEdit, QComboBox*& userTypeComboBox,
                                      QCheckBox*& userMailingDataCheck, QPushButton*& objectsButton,
                                      QPushButton*& actionButton, QLabel*& errorLabel)
{
    QDialog *dialog = new QDialog(this);
    QVBoxLayout *layout = new QVBoxLayout(dialog);

    // Инициализация элементов
    userLoginEdit = new QLineEdit();
    QLabel *userLoginLabel = new QLabel("Логін:");

    userWorkPositionEdit = new QLineEdit();
    QLabel *userWorkPositionLabel = new QLabel("Посада:");

    userTypeComboBox = new QComboBox();
    QStringList userTypes;
    userTypes << "Адмін" << "Користувач";
    userTypeComboBox->addItems(userTypes);

    QLabel *userMailLabel = new QLabel("Розсилання даних:");
    userMailingDataCheck = new QCheckBox();
    userMailingDataCheck->setChecked(true);
    userMailingDataCheck->setEnabled(false);

    objectsButton = new QPushButton("Список об'єктів");
    connect(objectsButton, &QPushButton::clicked, this, &MainWindow::SelectObjects);
    objectsButton->setEnabled(false);
    actionButton = new QPushButton();  // Название кнопки будет зависеть от операции

    // Лейбл для ошибок
    errorLabel = new QLabel();
    errorLabel->setStyleSheet("color: red;");
    errorLabel->setVisible(false);

    // Добавляем виджеты в layout
    layout->addWidget(userLoginLabel);
    layout->addWidget(userLoginEdit);
    layout->addWidget(userWorkPositionLabel);
    layout->addWidget(userWorkPositionEdit);
    layout->addWidget(errorLabel);
    layout->addWidget(new QLabel("Тип користувача:"));
    layout->addWidget(userTypeComboBox);
    layout->addWidget(userMailLabel);
    layout->addWidget(userMailingDataCheck);
    layout->addWidget(objectsButton);
    layout->addWidget(actionButton);

    dialog->setLayout(layout);

    // Подключаем сигнал для изменения состояния чекбокса
    connect(userTypeComboBox, &QComboBox::currentIndexChanged, this, [=](int index)
    {
        if (index == 0) // Если выбран "Адмін"
        {
            userMailingDataCheck->setEnabled(false);
            objectsButton->setEnabled(false);
        }
        else if (index == 1) // Если выбран "Користувач"
        {
            userMailingDataCheck->setEnabled(true);
            objectsButton->setEnabled(true);
        }
    });
    return dialog;
}

// Метод для проверки выбранных объектов
bool MainWindow::CheckObjectsSelection(const QString& userType)
{
    if (selectedObjects.isEmpty() && userType != "Адмін")
    {
        QMessageBox::critical(this, "Помилка", "Об'єкти не вибрано. Виберіть принаймні один об’єкт для користувача.");
        return false;
    }
    return true;
}

// Метод для заполнения объектов у админа
void MainWindow::FillAdminObjects(int userID)
{
    // Запрос для получения всех unit_id
    QSqlQuery query;
    query.prepare("SELECT id FROM [ReconDB].[dbo].[units]");

    if (!query.exec())
    {
        QMessageBox::critical(this, "Помилка", "Не вдалося отримати об'єкти: " + query.lastError().text());
        return;
    }

    // Перебираем все найденные unit_id
    while (query.next())
    {
        int unitID = query.value(0).toInt();

        // Проверяем, существует ли запись для этого unit_id и user_id в users_units
        QSqlQuery checkQuery;
        checkQuery.prepare("SELECT COUNT(*) FROM [ReconDB].[dbo].[users_units] WHERE unit_id = :unitID AND user_id = :userID");
        checkQuery.bindValue(":unitID", unitID);
        checkQuery.bindValue(":userID", userID);

        if (!checkQuery.exec())
        {
            QMessageBox::critical(this, "Помилка", "Не вдалося перевірити, чи існує підприємства у адміністратора: " + checkQuery.lastError().text());
            return;
        }

        if (!checkQuery.next())
        {
            return;
        }

        int count = checkQuery.value(0).toInt();

        if (count == 0) // Если запись не существует, вставляем новую
        {
            QSqlQuery insertQuery;
            insertQuery.prepare("INSERT INTO [ReconDB].[dbo].[users_units] (unit_id, user_id) VALUES (:unitID, :userID)");
            insertQuery.bindValue(":unitID", unitID);
            insertQuery.bindValue(":userID", userID);

            if (!insertQuery.exec())
            {
                QMessageBox::critical(this, "Помилка", "Не вдалося вставити підприємства адміністратора: " + insertQuery.lastError().text());
                return;
            }
        }
    }
}

// Метод для заполнения объектов у пользователя
void MainWindow::FillUserObjects(int userID)
{
    QSqlQuery query;

    for (const QString& fullObjectName : selectedObjects)
    {
        qDebug() << fullObjectName;
        QStringList parts = fullObjectName.split(". ");
        if (parts.size() != 2)
        {
            QMessageBox::critical(this, "Помилка", "Недійсний формат об'єкта: " + fullObjectName);
            return;
        }

        QString unit = parts[0];
        QString object = parts[1];

        query.prepare("SELECT id FROM [ReconDB].[dbo].[units] WHERE substation = :object");
        query.bindValue(":object", object);

        if (!query.exec() || !query.next())
        {
            QMessageBox::critical(this, "Помилка", "Помилка при пошуку підприжмства: " + unit);
            return;
        }

        int unitID = query.value(0).toInt();

        query.prepare("SELECT COUNT(*) FROM [ReconDB].[dbo].[users_units] WHERE unit_id = :unitID AND user_id = :userID");
        query.bindValue(":unitID", unitID);
        query.bindValue(":userID", userID);

        if (!query.exec() || !query.next())
        {
            QMessageBox::critical(this, "Помилка", "Не вдалось перевірити інування об'єктів у куристувача: " + query.lastError().text());
            return;
        }

        if (query.value(0).toInt() == 0)
        {
            query.prepare("INSERT INTO [ReconDB].[dbo].[users_units] (unit_id, user_id) VALUES (:unitID, :userID)");
            query.bindValue(":unitID", unitID);
            query.bindValue(":userID", userID);

            if (!query.exec()) {
                QMessageBox::critical(this, "Помилка", "Помилка при вставленні обхектів користувача: " + query.lastError().text());
                return;
            }
        }
    }
}

QString hashPassword(const QString& password) {
    QByteArray hash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
    return hash.toHex();
}

// Метод добавления пользователя в бд
void MainWindow::AddUserToDB()
{
    QLineEdit* userLoginEdit = nullptr;
    QLineEdit* userWorkPositionEdit = nullptr;
    QComboBox* userTypeComboBox = nullptr;
    QCheckBox* userMailingDataCheck = nullptr;
    QPushButton* objectsButton = nullptr;
    QPushButton* addButton = nullptr;
    QLabel* errorLabel = nullptr;
    selectedObjects.clear();

    QDialog* dialog = CreateUserDialog(userLoginEdit, userWorkPositionEdit, userTypeComboBox, userMailingDataCheck, objectsButton, addButton, errorLabel);
    if (!dialog || !userLoginEdit || !userWorkPositionEdit || !userTypeComboBox || !userMailingDataCheck || !objectsButton || !addButton || !errorLabel)
    {
        QMessageBox::critical(this, "Error", "Failed to create user dialog with required widgets.");
        return;
    }
    addButton->setText("Додати");

    const QString defaultPass = hashPassword("password");
    const QString defaultPlacing = "C:/Recon/WinRec-BS";

    // Логика при нажатии на кнопку "Додати"
    connect(addButton, &QPushButton::clicked, this, [=]()
            {
                QString userLogin = userLoginEdit->text();
                QString userWorkPosition = userWorkPositionEdit->text();
                QString userType = userTypeComboBox->currentText();
                bool userMailingData = userMailingDataCheck->isChecked();

                // Проверка на ввод логина
                if (userLogin.isEmpty())
                {
                    userLoginEdit->setStyleSheet("border: 1px solid red;");
                    errorLabel->setText("Логін не може бути порожнім");
                    errorLabel->setVisible(true);
                    return;
                }

                if (userWorkPosition.isEmpty())
                {
                    userWorkPositionEdit->setStyleSheet("border: 1px solid red;");
                    errorLabel->setText("Посада не може бути порожньою");
                    errorLabel->setVisible(true);
                    return;
                }

                // Проверка, что логин заканчивается на "@ua.energy"
                static const QRegularExpression emailPattern(R"(^[a-zA-Z0-9._%+-]+@ua\.energy$)");

                if (!emailPattern.match(userLogin).hasMatch())
                {
                    userLoginEdit->setStyleSheet("border: 1px solid red;");
                    errorLabel->setText("Логін має бути у форматі:\nname@ua.energy");
                    errorLabel->setVisible(true);
                    return;
                }
                else
                {
                    userLoginEdit->setStyleSheet("");  // Сбрасываем стиль при успешной проверке
                    errorLabel->setVisible(false);     // Скрываем сообщение об ошибке
                }

                // Проверка на выбор объектов
                if (!CheckObjectsSelection(userType))
                {
                    return;
                }

                QSqlQuery query;
                // Проверка на существования пользователя с таким логином
                query.prepare("SELECT id FROM [ReconDB].[dbo].[users] WHERE [login] = :userLogin");
                query.bindValue(":userLogin", userLogin);

                if (!query.exec())
                {
                    QMessageBox::critical(this, "Помилка", "Не вдалося перевірити, чи існує користувач: " + query.lastError().text());
                    return;
                }

                if (query.next())
                {
                    userLoginEdit->setStyleSheet("border: 1px solid red;");
                    errorLabel->setText("Користувач з логіном '" + userLogin + "'\nвже існує.");
                    errorLabel->setVisible(true);
                    return;
                }

                // Добавление нового пользователя
                query.prepare("INSERT INTO [ReconDB].[dbo].[users] (login, password, type, send_mail, winrec_path, post, status) "
                              "VALUES (:userLogin, :userPass, :userType, :sendMail , :winrecPath, :post, :status)");
                query.bindValue(":userLogin", userLogin);
                query.bindValue(":userPass", defaultPass);
                query.bindValue(":userType", userType);
                query.bindValue(":sendMail", userMailingData);
                query.bindValue(":winrecPath", defaultPlacing);
                query.bindValue(":post", userWorkPosition);
                query.bindValue(":status", true);

                if (!query.exec())
                {
                    QMessageBox::critical(this, "Помилка", "Не вдалося додати нового користувача: " + query.lastError().text());
                    return;
                }

                int userID = query.lastInsertId().toInt();

                if (userType == "Адмін")
                {
                    FillAdminObjects(userID);
                }
                else
                {
                    FillUserObjects(userID);
                }

                QMessageBox::information(this, "Успішно", "Користувача успішно додано!");
                LoadUsers();
                dialog->accept();
            });

    dialog->exec();
}


// Метод обновление параметров пользователя
void MainWindow::UpdateUser()
{
    // Получаем номер выбранной строки
    int currentRow = ui->userTableWidget->currentRow();
    if (currentRow == -1)
    {
        QMessageBox::warning(this, "Помилка", "Будь-ласка оберіть хоча б одного користувача.");
        return;
    }

    // Получаем логин полизователя для редактирования параметров
    QString userLogin = ui->userTableWidget->item(currentRow, 0)->text();
    updateSelectedObjects(currentRow);
    QSqlQuery query;

    query.prepare("SELECT id, type, send_mail, post FROM [ReconDB].[dbo].[users] WHERE [login] = :userLogin");
    query.bindValue(":userLogin", userLogin);

    if (!query.exec())
    {
        QMessageBox::critical(this, "Помилка", "Не вдалося перевірити, чи існує користувач: " + query.lastError().text());
        return;
    }

    // Проверяем, если ли пользователь в БД
    if (!query.next())
    {
        QMessageBox::warning(this, "Помилка", "Користувача не знайдено в базі даних.");
        return;
    }

    // Получаем ID пользователя
    int userID = query.value(0).toInt();
    QString userType = query.value(1).toString();
    bool userMailingData = query.value(2).toInt() == 1;
    QString post = query.value(3).toString();

    // Создаем диалоговое окно
    QLineEdit* userLoginEdit;
    QLineEdit* userWorkPositionEdit;
    QComboBox* userTypeComboBox;
    QCheckBox* userMailingDataCheck;
    QPushButton* objectsButton;
    QPushButton* updateButton;
    QLabel* errorLabel;

    QDialog* dialog = CreateUserDialog(userLoginEdit, userWorkPositionEdit, userTypeComboBox, userMailingDataCheck, objectsButton, updateButton, errorLabel);
    updateButton->setText("Редагувати");
    userLoginEdit->setText(userLogin);
    userWorkPositionEdit->setText(post);
    userLoginEdit->setReadOnly(true);
    userTypeComboBox->setCurrentText(userType);
    userMailingDataCheck->setChecked(userMailingData);

    // Определяем логику при нажатии на кнопку "Оновити"
    connect(updateButton, &QPushButton::clicked, this, [=]()
    {
        QString userLogin = userLoginEdit->text();
        QString userType = userTypeComboBox->currentText();
        QString userWorkPosition = userWorkPositionEdit->text();
        bool userMailingData = userMailingDataCheck->isChecked();

        // Проверка на выбор объектов
        if(!CheckObjectsSelection(userType))
        {
            return;
        }

        QSqlQuery updateQuery;

        // Обновление статуса пользователя
        updateQuery.prepare("UPDATE [ReconDB].[dbo].[users] SET [type] = :userType, [post] = :post, [send_mail] = :send_mail"
                            " WHERE [login] = :userLogin");
        updateQuery.bindValue(":userType", userType);
        updateQuery.bindValue(":userLogin", userLogin);
        updateQuery.bindValue(":post", userWorkPosition);
        updateQuery.bindValue(":send_mail", userMailingData);

        // Выполняем запрос обновления
        if (!updateQuery.exec())
        {
            QMessageBox::critical(this, "Помилка", "Не вдалося оновити дані користувача: " + updateQuery.lastError().text());
            return;
        }

        // Удаление старых привязок пользователя к объектам
        updateQuery.prepare("DELETE FROM [ReconDB].[dbo].[users_units] WHERE user_id = :userID");
        updateQuery.bindValue(":userID", userID);

        if (!updateQuery.exec())
        {
            QMessageBox::critical(this, "Помилка", "Помилка при видаленні старих об'єктів користувача: " + updateQuery.lastError().text());
            return;
        }

        // В зависимости от типа пользователя, заполняем объекты
        if (userType == "Адмін")
        {
            FillAdminObjects(userID);
        }
        else
        {
            FillUserObjects(userID);
        }

        QMessageBox::information(this, "Успішно", "Користувача успішно оновлено!");
        LoadUsers();
        dialog->accept();
    });

    dialog->exec();
}

void MainWindow::updateSelectedObjects(int userRow)
{
    // Очистка списка перед обновлением
    selectedObjects.clear();

    // Получение QComboBox из таблицы
    QComboBox *objectsComboBox = qobject_cast<QComboBox *>(ui->userTableWidget->cellWidget(userRow, 2));
    if (!objectsComboBox)
    {
        qWarning() << "Failed to find objects combo box in row" << userRow;
        return;
    }

    // Получение списка объектов из QComboBox
    for (int i = 0; i < objectsComboBox->count(); ++i)
    {
        QString object = objectsComboBox->itemText(i);
        selectedObjects.append(object);
    }

    qDebug() << "Updated selectedObjects:" << selectedObjects;
}


// Метод удаления пользователя
void MainWindow::DeleteUser()
{
    // Получаем номер выбранной строки
    int currentRow = ui->userTableWidget->currentRow();
    if (currentRow == -1)
    {
        QMessageBox::critical(this, "Помилка", "Будь-ласка оберіть хоча б один рядок.");
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Підтвердження", "Вы впевненні, що хочете видалити користувача?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        // Получаем логин пользователя для удаления
        const QString userLogin = ui->userTableWidget->item(currentRow, 0)->text();

        QSqlQuery query;

        query.prepare("DELETE FROM [ReconDB].[dbo].[users] WHERE [login] = :userLogin");
        query.bindValue(":userLogin", userLogin);

        if (!query.exec())
        {
            QMessageBox::critical(this, "Помилка", "Не вдалося видалити користувача: " + query.lastError().text());
            return;
        }

        QMessageBox::information(this, "Успішно", "Користувача успішно видалено!");
    }
    else
    {
        QMessageBox::information(this, "Інформація", "Видалення користувача скасовано.");
    }

    LoadUsers();
}

// Метод для создания списка всех предприятий и объектов
void MainWindow::SelectObjects()
{
    QSqlQuery query;

    // Исправленный SQL-запрос для получения всех предприятий и их подстанций
    QString command = "SELECT [unit], [substation] "
                      "FROM [ReconDB].[dbo].[units] "
                      "ORDER BY [unit], [substation]";
    query.prepare(command);

    if (!query.exec())
    {
        QMessageBox::critical(this, "Error", "Failed to execute query: " + query.lastError().text());
        return;
    }

    // Создаем диалог для выбора объектов
    QDialog dialog(this);
    dialog.setWindowTitle("Вибір об'єктів");

    QVBoxLayout *layout = new QVBoxLayout(&dialog);

    // Используем QTreeWidget для организации объектов по предприятиям
    QTreeWidget *treeWidget = new QTreeWidget;
    treeWidget->setHeaderHidden(true);
    treeWidget->setSelectionMode(QAbstractItemView::MultiSelection);

    QMap<QString, QTreeWidgetItem*> unitMap;

    while (query.next())
    {
        QString unit = query.value(0).toString();       // Предприятие (unit)
        QString substation = query.value(1).toString(); // Подстанция (substation)

        if (!unitMap.contains(unit))
        {
            // Если предприятие не добавлено, добавляем его
            QTreeWidgetItem *unitItem = new QTreeWidgetItem(treeWidget);
            unitItem->setText(0, unit);
            unitMap[unit] = unitItem;
        }

        // Добавляем подстанцию как дочерний элемент предприятия
        QTreeWidgetItem *substationItem = new QTreeWidgetItem(unitMap[unit]);
        substationItem->setText(0, substation);

        // Проверяем, если объект уже выбран, выделяем его
        QString fullObjectName = unit + ". " + substation;
        if (selectedObjects.contains(fullObjectName))
        {
            substationItem->setSelected(true);
        }
    }

    // Подключаем сигнал для обработки изменения выделения элементов
    connect(treeWidget, &QTreeWidget::itemSelectionChanged, [=]()
    {
        // Проходим по всем элементам и проверяем, если родитель выбран — выделяем всех детей
        for (auto unitItem : unitMap)
        {
            // Если родительский элемент выбран, выбираем всех дочерних, если не выбран — оставляем состояние дочерних элементов без изменений
            if (unitItem->isSelected())
            {
                for (int i = 0; i < unitItem->childCount(); ++i)
                {
                    QTreeWidgetItem *substationItem = unitItem->child(i);
                    if (!substationItem->isSelected()) // Выделяем только невыделенные
                    {
                        substationItem->setSelected(true);
                    }
                }
            }
        }
    });

    // Добавляем виджет с деревом в диалог
    layout->addWidget(treeWidget);

    // Кнопка OK для подтверждения выбора
    QPushButton *okButton = new QPushButton("OK");
    layout->addWidget(okButton);
    connect(okButton, &QPushButton::clicked, &dialog, &QDialog::accept);

    dialog.setLayout(layout);
    qDebug() << selectedObjects ;
    // Обрабатываем результат выбора
    if (dialog.exec() == QDialog::Accepted)
    {
        // Очищаем список выбранных объектов
        selectedObjects.clear();

        QList<QTreeWidgetItem *> selectedItems = treeWidget->selectedItems();

        for (QTreeWidgetItem *item : selectedItems)
        {
            if (item->childCount() == 0)    // Проверяем, что это подстанция, а не предприятие
            {
                QString unit = item->parent()->text(0);  // Получаем название предприятия
                QString substation = item->text(0);      // Получаем название подстанции

                QString fullObjectName = unit + ". " + substation;
                selectedObjects.append(fullObjectName);
            }
        }
    }
}

// Метод для обновления статуса пользователя в базе данных
void MainWindow::UpdateUserStatus(int userID, bool isActive)
{
    QSqlQuery query;
    query.prepare("UPDATE [ReconDB].[dbo].[users] SET [status] = :status WHERE [id] = :id");
    query.bindValue(":status", isActive ? true : false);
    query.bindValue(":id", userID);

    if (!query.exec())
    {
        QMessageBox::critical(this, "Помилка", "помилка оновлення статуса користувача: " + query.lastError().text());
        return;
    }

    LoadUsers();
}

// Метод изменения пароля (по кнопке)
void MainWindow::HandleChangePassword(int userID) {
    bool ok;
    QString newPassword = QInputDialog::getText(this, tr("Зміна пароля"),
                                                tr("Введіть новий пароль:"), QLineEdit::Password,
                                                "", &ok);
    QString hashedPassword = hashPassword(newPassword);
    if (ok && !hashedPassword.isEmpty()) {
        QSqlQuery query;
        query.prepare("UPDATE [ReconDB].[dbo].[users] SET [password] = :hashedPassword WHERE [id] = :userID");
        query.bindValue(":hashedPassword", hashedPassword);  // Лучше использовать хэширование пароля, например, с использованием SHA-256
        query.bindValue(":userID", userID);

        if (query.exec()) {
            QMessageBox::information(this, tr("Успішно"), tr("Пароль успішно змінено."));
        } else {
            QMessageBox::critical(this, tr("Помилка"), tr("Не вдалося змінити пароль: %1").arg(query.lastError().text()));
        }
    }
}

void MainWindow::toggleRowVisibility(int lastRow, int parentColumn, bool collapse)
{
    qDebug() << "lastRow: " << lastRow;
    qDebug() << "parentColumn: " << parentColumn;
    qDebug() << "collapse: " << collapse;

    QString parentItem = ui->serviceTreeTableWidget->item(lastRow, parentColumn)->text();
    QSet<QString> seenIPs; // Для отслеживания уникальных IP

    bool hideRow;

    // Проходим все строки, относящиеся к текущему объекту или предприятию
    for (int row = 0; row <= lastRow; ++row) {
        QTableWidgetItem *parentItemCell = ui->serviceTreeTableWidget->item(row, parentColumn);
        QTableWidgetItem *ipItem = ui->serviceTreeTableWidget->item(row, 4); // IP-адрес

        if (!parentItemCell || !ipItem) continue;

        QString ipAddress = ipItem->text();

        // Проверка соответствия объекта или предприятия
        if (parentItemCell->text() == parentItem) {
            if (!seenIPs.contains(ipAddress)) {
                seenIPs.insert(ipAddress); // Оставляем первую строку для IP
                hideRow = false;
            } else {
                hideRow = collapse; // Остальные строки с этим IP скрываются
            }
            ui->serviceTreeTableWidget->setRowHidden(row, hideRow);
        }
    }
}


void MainWindow::AddTextWithButton(int row, int column, const QString &text)
{
    QWidget *containerWidget = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout(containerWidget);
    layout->setContentsMargins(0, 0, 0, 0);

    QLabel *textLabel = new QLabel(text);
    QFont font = textLabel->font();
    font.setFamily("Tahoma");
    font.setBold(false);
    textLabel->setFont(font);
    textLabel->setStyleSheet("background-color: transparent;");

    QPushButton *toggleButton = new QPushButton("▼");
    toggleButton->setFixedSize(20, 20);

    connect(toggleButton, &QPushButton::clicked, [this, row, column, toggleButton]() {
        bool isCollapsed = (toggleButton->text() == "▼");
        toggleButton->setText(isCollapsed ? ">" : "▼");
        toggleRowVisibility(row, column, isCollapsed);
    });

    layout->addWidget(textLabel);
    layout->addWidget(toggleButton);
    layout->setAlignment(Qt::AlignLeft);

    ui->serviceTreeTableWidget->setItem(row, column, nullptr);

    ui->serviceTreeTableWidget->setCellWidget(row, column, containerWidget);
}

void mergeRepeatedCells(QTableWidget* table) {
    if (!table) return;

    const int rowCount = table->rowCount();

    QVariant prevEnterprise, prevSubstation, prevIp;
    int startEnterpriseRow = -1, startSubstationRow = -1, startIpRow = -1;

    for (int row = 0; row <= rowCount; ++row) {
        QVariant enterprise, substation, ip;

        if (row < rowCount) {
            enterprise = table->item(row, 1) ? table->item(row, 1)->text() : "";
            substation = table->item(row, 2) ? table->item(row, 2)->text() : "";
            ip         = table->item(row, 4) ? table->item(row, 4)->text() : "";
        }

        // Предприятие (столбец 1)
        if (enterprise != prevEnterprise || row == rowCount) {
            int span = row - startEnterpriseRow;
            if (startEnterpriseRow != -1 && span > 1) {
                table->setSpan(startEnterpriseRow, 1, span, 1);
            }
            startEnterpriseRow = row;
            prevEnterprise = enterprise;
        }

        // Подстанция (столбец 2)
        if (substation != prevSubstation || row == rowCount) {
            int span = row - startSubstationRow;
            if (startSubstationRow != -1 && span > 1) {
                table->setSpan(startSubstationRow, 2, span, 1);
            }
            startSubstationRow = row;
            prevSubstation = substation;
        }

        // IP-адрес (столбец 4 и последний)
        if (ip != prevIp || row == rowCount) {
            int span = row - startIpRow;
            if (startIpRow != -1 && span > 1) {
                table->setSpan(startIpRow, 4, span, 1);
                table->setSpan(startIpRow, table->columnCount() - 1, span, 1);
            }
            startIpRow = row;
            prevIp = ip;
        }
    }
}


void clearAllSpans(QTableWidget* table) {
    for (int row = 0; row < table->rowCount(); ++row) {
        for (int col = 0; col < table->columnCount(); ++col) {
            table->setSpan(row, col, 1, 1);
        }
    }
}

// Метод загрузки дерева объектов
void MainWindow::LoadServiceTree()
{
    int columnCount = 11;
    // Очистка таблицы перед загрузкой данных
    ui->serviceTreeTableWidget->clear();
    ui->serviceTreeTableWidget->setRowCount(0);
    ui->serviceTreeTableWidget->setColumnCount(columnCount);

    // Установка заголовков таблицы
    ui->serviceTreeTableWidget->setHorizontalHeaderLabels(QStringList()
                                                          << "unit_id" << "Підприємство" << "Об'єкт" << "№ рекона"
                                                          << "IP адреса сервера" << "Віддалена папка" << "Локальная папка" << "struct_id"
                                                          << "Минуле підприємство" << "Чотирьохзначний?" << "Активний/неактивний");

    // SQL-запрос для получения данных
    QSqlQuery query("SELECT U.[id] AS [unit_id], "
                    "U.[unit] AS [Підприємство], "
                    "U.[substation] AS [Об'єкт], "
                    "S.[recon_id] AS [№ рекона], "
                    "FS.[IP_addr] AS [IP адреса сервера], "
                    "FD.[remote_path] AS [Віддалена папка], "
                    "FD.[isFourDigits] AS [Чотирьохзначний?], "
                    "S.[files_path] AS [Локальна папка], "
                    "FS.[status] AS [Статус], "
                    "S.[id] AS [struct_id],"
                    "FS.[previous_unit] AS [Минуле підприємство],"
                    "FS.[login] AS [IP адреса сервера], "
                    "FS.[password] AS [IP адреса сервера] "
                    "FROM [ReconDB].[dbo].[units] U "
                    "JOIN [ReconDB].[dbo].[struct_units] SU ON U.[id] = SU.[unit_id] "
                    "JOIN [ReconDB].[dbo].[struct] S ON SU.[struct_id] = S.[id] "
                    "LEFT JOIN [ReconDB].[dbo].[FTP_servers] FS ON U.[id] = FS.[unit_id] "
                    "LEFT JOIN [ReconDB].[dbo].[FTP_Directories] FD ON S.[id] = FD.[struct_id]"
                    "ORDER BY U.[unit], FS.[IP_addr]");

    bool showOnlyFilled = ui->filledParamsCheck->isChecked(); // Проверка состояния чекбокса

    // Переменные для отслеживания предыдущих значений и строк для объединения
    int previousEnterpriseRow = -1;
    int previousSubstationRow = -1;
    int previousIpAddressRow = -1;

    QString previousEnterprise;
    QString previousSubstation;
    QString previousIpAddress;

    QMap<QString, QCheckBox*> ipCheckBoxes;

    while (query.next())
    {
        int row = ui->serviceTreeTableWidget->rowCount();
        ui->serviceTreeTableWidget->insertRow(row);

        QString enterpriseName = query.value(1).toString();
        QString substationName = query.value(2).toString();

        int statusCode = query.value(8).toInt();

        QString ftpLogin = query.value(11).toString();
        QString ftpPassword = query.value(12).toString();

        // Создаем чекбокс для 4-x значных регистраторов, если его еще нет
        QString remotePath = query.value(5).toString();
        int isFourDigitsRes = query.value(6).toInt();
        QCheckBox *isFourDigits = nullptr;

        isFourDigits = new QCheckBox();
        isFourDigits->setChecked(isFourDigitsRes == 1);
        // isFourDigits->setEnabled(statusCode != 2);

        connect(isFourDigits, &QCheckBox::checkStateChanged, [this, remotePath](int state) {
            UpdateFourDigitsStatus(remotePath, state == Qt::Checked);
        });

        // ipCheckBoxes[ipAddress] = isServerOnCheck;


        // Создаем чекбокс для айпи, если его еще нет
        QString ipAddress = query.value(4).toString();
        QCheckBox *isServerOnCheck = nullptr;

        if (!ipCheckBoxes.contains(ipAddress)) {
            isServerOnCheck = new QCheckBox();
            isServerOnCheck->setChecked(statusCode == 1);
            isServerOnCheck->setEnabled(statusCode != 2);

            connect(isServerOnCheck, &QCheckBox::checkStateChanged, [this, ipAddress](int state) {
                UpdateFactoryStatus(ipAddress, state == Qt::Checked);
            });

            ipCheckBoxes[ipAddress] = isServerOnCheck;
        } else {
            isServerOnCheck = ipCheckBoxes[ipAddress];
        }

        // Заполнение данных
        QStringList rowData;
        rowData << query.value(0).toString()    // ID
                << query.value(1).toString()    // Підприємство
                << query.value(2).toString()    // Об'єкт
                << query.value(3).toString()    // № рекона
                << query.value(4).toString()    // IP адреса сервера
                << query.value(5).toString()    // Віддалена папка
                << query.value(7).toString()    // Локальная папка
                << query.value(9).toString()    // struct_id Для таблицы директорий
                << query.value(10).toString();  // Минуле підприємство

        // // Логика объединения ячеек
        // int spanEnterpriseSize = row + 1;
        // int spanSubstationSize = row + 1;
        // int spanIpAddressSize  = row + 1;
        // if (previousEnterprise == rowData[1] && !rowData[1].isEmpty()) {
        //     spanEnterpriseSize -= previousEnterpriseRow;
        //     if (spanEnterpriseSize > 1) {
        //         ui->serviceTreeTableWidget->setSpan(previousEnterpriseRow, 1, spanEnterpriseSize, 1);
        //     }
        // } else {
        //     previousEnterprise = rowData[1];
        //     previousEnterpriseRow = row;
        // }

        // // Проверка на одинаковую підстанцію
        // if (previousSubstation == substationName && !substationName.isEmpty()) {
        //     spanSubstationSize -= previousSubstationRow;
        //     if (spanSubstationSize > 1) {
        //         ui->serviceTreeTableWidget->setSpan(previousSubstationRow, 2, spanSubstationSize, 1); // Об'єкт
        //     }
        // } else {
        //     previousSubstation = substationName;
        //     previousSubstationRow = row;
        // }

        // // Проверка на одинаковый IP-адрес
        // if (previousIpAddress == rowData[4] && !rowData[4].isEmpty()) {
        //     spanIpAddressSize -= previousIpAddressRow;
        //     if(spanIpAddressSize > 1){
        //         ui->serviceTreeTableWidget->setSpan(previousIpAddressRow, 4, row - previousIpAddressRow + 1, 1);
        //         ui->serviceTreeTableWidget->setSpan(previousIpAddressRow, columnCount - 1, spanIpAddressSize, 1);
        //     }
        // } else {
        //     previousIpAddress = rowData[4];
        //     previousIpAddressRow = row;
        // }

        bool hasEmptyFields = false;

        // Проверка строки на наличие пустых полей
        for (int col = 0; col < rowData.size(); ++col) {
            if (rowData[col].isEmpty()) {
                hasEmptyFields = true;
                break;
            }
        }

        // Если активен чекбокс и в строке есть пустые поля, скрываем строку
        if (showOnlyFilled && hasEmptyFields) {
            ui->serviceTreeTableWidget->setRowHidden(row, true);
        } else {
            QString remoteFolder = rowData[5];
            QString ipAddress = rowData[4];
            QString local_path = rowData[6];
            QString struct_id = rowData[7];

            // Добавляем строку в таблицу и делаем её видимой
            for (int col = 0; col < rowData.size(); ++col) {
                QTableWidgetItem *item = new QTableWidgetItem(rowData[col]);

                // if(col == 1 || col == 2){
                //     AddTextWithButton(row, col, rowData[col]);
                // }

                // Скрываем столбец с ID, local_path и struct_id
                if (col == 0 || col == 6 || col == 7 || col == 8) {
                    ui->serviceTreeTableWidget->setColumnHidden(col, true);
                }

                // Закрашиваем ячейки, только если это не чекбокс (последняя колонка) и колонка меньше 8
                if (statusCode == 2 && col < columnCount - 1 && col > 1) {
                    item->setBackground(Qt::yellow);
                }

                if (statusCode == 0 && col < columnCount - 1 && col > 2) {
                    item->setBackground(Qt::darkGray);
                }

                // Устанавливаем элементы, кроме последней колонки (где чекбокс)
                if (col < columnCount - 2) {
                    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                    ui->serviceTreeTableWidget->setItem(row, col, item);
                }

                if (col == 5 && !ipAddress.isEmpty() && item->background().color().name() != "#ffff00") {
                    if (!CheckFtpFolderExists(ipAddress, remoteFolder, ftpLogin, ftpPassword)) {
                        item->setBackground(Qt::red);
                    }
                }
            }
            // Добавляем чекбокс четырёхзначиных реконов
            ui->serviceTreeTableWidget->setCellWidget(row, columnCount - 2, isFourDigits);

            // Добавляем чекбокс в последнюю колонку
            ui->serviceTreeTableWidget->setCellWidget(row, columnCount - 1, isServerOnCheck);

            // Делаем строку видимой
            ui->serviceTreeTableWidget->setRowHidden(row, false);
        }
    }

    FillMissingData();

    clearAllSpans(ui->serviceTreeTableWidget);
    mergeRepeatedCells(ui->serviceTreeTableWidget);

    ui->serviceTreeTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->serviceTreeTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->serviceTreeTableWidget->resizeColumnsToContents();
    ui->serviceTreeTableWidget->resizeRowsToContents();
    ui->serviceTreeTableWidget->verticalHeader()->setVisible(false);

    ui->serviceTreeTableWidget->horizontalHeader()->setStretchLastSection(true);
}

void MainWindow::FillMissingData()
{
    for (int row = 0; row < ui->serviceTreeTableWidget->rowCount(); ++row)
    {
        QTableWidgetItem *remotePathItem = ui->serviceTreeTableWidget->item(row, 5);        // "Віддалена папка"
        if (remotePathItem && remotePathItem->text().isEmpty())
        {
            QString struct_id = ui->serviceTreeTableWidget->item(row, 7)->text();           // struct_id
            QString local_path = ui->serviceTreeTableWidget->item(row, 6)->text();          // Локальная папка
            QString remote_path = "R" + ui->serviceTreeTableWidget->item(row, 3)->text();   // № рекона

            InsertDirValue(struct_id, remote_path, local_path);

            // Обновление значения в таблице для отображения
            remotePathItem->setText(remote_path);
        }
    }
}

void MainWindow::InsertDirValue(QString struct_id, QString remote_path, QString local_path)
{
    QSqlQuery query;
    query.prepare(R"(
        MERGE INTO [ReconDB].[dbo].[FTP_Directories] AS target
        USING (SELECT :struct_id AS struct_id, :remotePath AS remote_path, :localPath AS local_path) AS source
        ON target.struct_id = source.struct_id AND target.remote_path = source.remote_path AND target.local_path = source.local_path
        WHEN NOT MATCHED THEN
            INSERT (struct_id, remote_path, local_path)
            VALUES (source.struct_id, source.remote_path, source.local_path);
    )");

    query.bindValue(":struct_id", struct_id);
    query.bindValue(":remotePath", QVariant(remote_path));
    query.bindValue(":localPath", QVariant(local_path));

    if (!query.exec()) {
        qDebug() << "Failed to execute MERGE query:" << query.lastError().text();
    }
}


// Проверка подключения к Ftp серверу
bool MainWindow::CheckFtpConnection(const QString &ipAddress, const QString &remoteFolder, const QString &username, const QString &password)
{
    CURL *curl;
    CURLcode res;
    bool status = false;

    qDebug() << "Попытка подключения к FTP:";
    qDebug() << "IP адрес: " << ipAddress;
    qDebug() << "Папка: " << remoteFolder;
    qDebug() << "Имя пользователя: " << username;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl) {
        QString url = QString("ftp://%1/").arg(ipAddress);

        curl_easy_setopt(curl, CURLOPT_URL, url.toStdString().c_str());
        curl_easy_setopt(curl, CURLOPT_USERNAME, username.toStdString().c_str());
        curl_easy_setopt(curl, CURLOPT_PASSWORD, password.toStdString().c_str());
        curl_easy_setopt(curl, CURLOPT_PORT, 21);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); // Подробный вывод от libcurl
        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 10L); // Таймаут подключения
        curl_easy_setopt(curl, CURLOPT_FTP_RESPONSE_TIMEOUT, 10L); // Таймаут ожидания ответа FTP

        res = curl_easy_perform(curl);

        if (res == CURLE_OK) {
            qDebug() << "FTP-соединение успешно установлено.";
            status = true;
        }
        else {
            qDebug() << "Ошибка подключения к FTP серверу:" << curl_easy_strerror(res) << "(код" << res << ")";
        }

        curl_easy_cleanup(curl);
    }
    else {
        qDebug() << "Не удалось инициализировать libcurl.";
    }

    curl_global_cleanup();
    return status;
}

bool MainWindow::CheckFtpFolderExists(const QString &ipAddress, const QString &remoteFolder,
                                      const QString &username, const QString &password)
{
    CURL* curl;
    CURLcode res;
    bool folderExists = false;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        QString url = QString("ftp://%1/%2/").arg(ipAddress).arg(remoteFolder);

        curl_easy_setopt(curl, CURLOPT_URL, url.toStdString().c_str());
        curl_easy_setopt(curl, CURLOPT_USERNAME, username.toStdString().c_str());
        curl_easy_setopt(curl, CURLOPT_PASSWORD, password.toStdString().c_str());
        curl_easy_setopt(curl, CURLOPT_PORT, 21);

        // Проверка существования папки
        curl_easy_setopt(curl, CURLOPT_NOBODY, 1L); // Не загружать данные, просто выполнить запрос
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "CWD"); // Выполнить команду смены директории

        res = curl_easy_perform(curl);

        if (res == CURLE_OK) {
            folderExists = true;
        } else {
            qDebug() << "Ошибка проверки папки на FTP: " << curl_easy_strerror(res);
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return folderExists;
}


// Слот, который вызывается при выборе строки
void MainWindow::OnFactorySelected(QTableWidgetItem *item)
{
    QModelIndexList selectedIndexes = ui->serviceTreeTableWidget->selectionModel()->selectedRows();
    qDebug() << "selectedIndexes: " << selectedIndexes;
    if (selectedIndexes.size() > 0)
    {
        int selectedRow = selectedIndexes[0].row();

        // Получаем данные всей строки
        QStringList rowData;
        for (int i = 0; i < ui->serviceTreeTableWidget->columnCount() - 2; ++i)
        {
            rowData << ui->serviceTreeTableWidget->item(selectedRow, i)->text();
        }

        // Открываем диалог с данными строки
        OpenFactoryDialog(rowData);
    }
}

// Метод для обновления статуса сервера в базе данных
void MainWindow::UpdateFactoryStatus(const QString& ipAddress, bool isActive)
{
    QSqlQuery query;

    query.prepare("UPDATE FTP_servers SET status = :status WHERE IP_addr = :ipAddress");
    query.bindValue(":status", isActive ? 1 : 0);
    query.bindValue(":ipAddress", ipAddress);
    if (!query.exec()) {
        qDebug() << "Ошибка обновления статуса сервера для IP:" << ipAddress << query.lastError();
    }

    LoadServiceTree();
}

void MainWindow::UpdateFourDigitsStatus(const QString& remotePath, bool isTrue){
    qDebug() << "UpdateFourDigitsStatus was started! Remote path: " + remotePath;
    QSqlQuery query;

    query.prepare("UPDATE [ReconDB].[dbo].[FTP_Directories] SET isFourDigits = :isTrue WHERE remote_path = :remotePath");
    query.bindValue(":remotePath", remotePath);
    query.bindValue(":isTrue", isTrue ? 1 : 0);
    if(!query.exec()){
        qDebug() << "Eror in function 'UpdateFourDigitsStatus' for remotePath: " << remotePath << query.lastError();
    } else {
        qDebug() << "UpdateFourDigitsStatus was succusfull finished!" << query.lastQuery();
    }
}

// Метод для обновления параметров сервера в базе данных
void MainWindow::UpdateIpParams(int &unit_id, QString &ipAddress, QString &prevIP, QString &ipLogin, QString &ipPassword,
                                QString &struct_id, QString &remotePath, QString &localPath, QString &previousUnit, bool isMultiple)
{
    QString status;

    if(CheckFtpConnection(ipAddress, remotePath, ipLogin, ipPassword))
    {
        status = "1";
    }
    else
    {
        status = "2";
    }

    qDebug() << "UpdateIpParams was started with isMultiple: " << isMultiple;
    qDebug() << "unit_id " <<  unit_id;
    qDebug() << "ipAddress " << ipAddress;
    qDebug() << "prevIP " << prevIP;
    QSqlQuery updateServerQuery;
    updateServerQuery.prepare(
        "UPDATE [ReconDB].[dbo].[FTP_servers] "
        "SET [IP_addr] = :ipAddress, "
        "[login] = :ipLogin, "
        "[password] = :ipPassword, "
        "[status] = :status, "
        "[previous_unit] = :previous_unit, "
        "[isMultiple] = :isMultiple, "
        "[unit_id] = CASE WHEN [unit_id] IS NULL THEN :unitId ELSE [unit_id] END "
        "WHERE ([unit_id] IS NOT NULL AND [IP_addr] = :prevIP) OR [unit_id] IS NULL"
        );

    updateServerQuery.bindValue(":unitId", unit_id);
    updateServerQuery.bindValue(":ipAddress", ipAddress);
    updateServerQuery.bindValue(":prevIP", prevIP);
    updateServerQuery.bindValue(":ipLogin", ipLogin);
    updateServerQuery.bindValue(":ipPassword", ipPassword);
    updateServerQuery.bindValue(":status", status);
    updateServerQuery.bindValue(":previous_unit", previousUnit);
    updateServerQuery.bindValue(":isMultiple", isMultiple ? 1 : 0);

    // Попробуем выполнить запрос
    if (!updateServerQuery.exec())
    {
        qDebug() << "Update failed: " << updateServerQuery.lastError().text();
        QMessageBox::critical(this, "Помилка", "Не вдалося оновити сервер: " + updateServerQuery.lastError().text());
    }
    else
    {
        if(status == "1")
        {
            QMessageBox::warning(this, "Підключення до сервера", "Зєднання з сервером успішно встановлено");
        }
        else
        {
            QMessageBox::warning(this, "Підключення до сервера", "Зєднання з сервером не було встановлено");
        }
    }

    QSqlQuery checkPathQuery;
    checkPathQuery.prepare("SELECT * FROM [ReconDB].[dbo].[FTP_Directories] "
                           "WHERE [struct_id] = :struct_id ");
    checkPathQuery.bindValue(":struct_id", struct_id);

    if (!checkPathQuery.exec()) {
        // Обработка ошибки выполнения запроса
        QMessageBox::critical(this, "Помилка", "Помилка при виконуванні запиту: " + checkPathQuery.lastError().text());
        return;
    }

    if (checkPathQuery.next())
    {

        // Обновления таблицы FTP_Directories
        QSqlQuery updateServerDirQuery;
        updateServerDirQuery.prepare("UPDATE [ReconDB].[dbo].[FTP_Directories] SET [remote_path] = :remotePath WHERE [struct_id] = :struct_id");
        updateServerDirQuery.bindValue(":remotePath", remotePath);
        updateServerDirQuery.bindValue(":struct_id", struct_id);

        if (!updateServerDirQuery.exec())
        {
            QMessageBox::critical(this, "Помилка", "Помилка оновлення шляху: " + updateServerDirQuery.lastError().text());
        }
    }
    else
    {
        // Записи нет, вставка в таблицу FTP_Directories
        qDebug() << "Записи нет, вставка в таблицу FTP_Directories\nstruct_id: " << struct_id;
        QSqlQuery insertServerDirQuery;
        insertServerDirQuery.prepare("INSERT INTO [ReconDB].[dbo].[FTP_Directories](struct_id, remote_path, local_path) "
                                     "VALUES(:struct_id, :remotePath, :localPath)");
        insertServerDirQuery.bindValue(":struct_id", struct_id);
        insertServerDirQuery.bindValue(":remotePath", remotePath);
        insertServerDirQuery.bindValue(":localPath", localPath);

        if (!insertServerDirQuery.exec())
        {
            QMessageBox::critical(this, "Помилка", "Помилка додавання шляху: " + insertServerDirQuery.lastError().text());
        }
    }

    LoadServiceTree();
}

void MainWindow::loadIpCredentials(const QString &ip, bool updateSubstationLabel, QLabel *substationLabel, QLineEdit *ipLoginEdit, QLineEdit *ipPasswordEdit, QCheckBox *ipMultipleCheckBox)
{
    QSqlQuery getCredentialsQuery;
    getCredentialsQuery.prepare("SELECT login, password, previous_unit, isMultiple FROM [ReconDB].[dbo].[FTP_servers] WHERE IP_addr = :ipAddress");
    getCredentialsQuery.bindValue(":ipAddress", ip);

    if (!getCredentialsQuery.exec())
    {
        qDebug() << "Query failed: " << getCredentialsQuery.lastError().text();
        return;
    }

    if (getCredentialsQuery.next())
    {
        QString login = getCredentialsQuery.value(0).toString();
        QString password = getCredentialsQuery.value(1).toString();
        bool isMultipleIP = getCredentialsQuery.value(3).toBool();

        qDebug() << "isMultipleIP form loadIpCredentails is " << isMultipleIP;

        ipLoginEdit->setText(login);
        ipPasswordEdit->setText(password);
        ipMultipleCheckBox->setChecked(isMultipleIP);

        if (updateSubstationLabel)
        {
            substationLabel->setText("Підстанція: " + getCredentialsQuery.value(2).toString());
            substationLabel->setVisible(true);
        }

        qDebug() << "isMultipleIP: " << isMultipleIP;
    }
    else
    {
        qDebug() << "No credentials found for IP:" << ip;
    }
}


// Метод для открытия диалогового окна
void MainWindow::OpenFactoryDialog(const QStringList &rowData)
{
    qDebug() << rowData;
    currentFactoryDialog = new QDialog(this);
    currentFactoryDialog->setWindowTitle("Заповніть параметри для підприємства");
    QVBoxLayout *layout = new QVBoxLayout(currentFactoryDialog);

    QLabel *ipAddressLabel = new QLabel("ІР адреса: ");
    QLineEdit *ipAddressEdit = new QLineEdit();
    ipAddressEdit->setText(rowData[4]);  // Заполнение IP адреса

    // Регулярное выражение для фильтрации ввода IP-адресов
    QRegularExpression ipRegex("^[0-9.]*$");  // Разрешает только цифры и точки
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(ipRegex, this);

    ipAddressEdit->setValidator(validator);

    // Новый виджет для отображения названия подстанции
    QLabel *substationLabel = new QLabel("");
    substationLabel->setVisible(false);

    // Создаем ComboBox для списка IP-адресов
    QComboBox *ipAddressComboBox = new QComboBox();
    ipAddressComboBox->addItem("");

    // Получаем список уникальных IP-адресов из базы данных
    QSqlQuery query;
    query.prepare("SELECT DISTINCT [IP_addr], [previous_unit] FROM [ReconDB].[dbo].[FTP_servers]");
    if (query.exec())
    {
        while (query.next())
        {
            QString ip = query.value(0).toString();
            QString previous_unit = query.value(1).toString();
            QString itemText = ip + " (" + previous_unit + ")";
            ipAddressComboBox->addItem(itemText, ip);
        }
    }

    // Логин и пароль
    QLabel *ipLoginLabel = new QLabel("Логін: ");
    QLineEdit *ipLoginEdit = new QLineEdit();

    QLabel *ipPasswordLabel = new QLabel("Пароль: ");
    QLineEdit *ipPasswordEdit = new QLineEdit();
    ipPasswordEdit->setEchoMode(QLineEdit::Password);

    QCheckBox *showPasswordCheckBox = new QCheckBox("");

    bool isMultipleIP;
    QCheckBox *ipMultipleCheckBox = new QCheckBox();
    QLabel *ipMultipleLabel = new QLabel("Збирає с декілької об'єктів?");

    // При первом открытии
    QString initialIpAddress = rowData[4];
    if (!initialIpAddress.isEmpty())
    {
        qDebug() << "initialIpAddress is not empty";
        loadIpCredentials(initialIpAddress, false, substationLabel, ipLoginEdit, ipPasswordEdit, ipMultipleCheckBox);
    }

    // При изменении IP в ComboBox
    connect(ipAddressComboBox, &QComboBox::currentIndexChanged, this, [=](int index)
    {
        QString selectedIp = ipAddressComboBox->itemData(index).toString();
        ipAddressEdit->setText(selectedIp);
        loadIpCredentials(selectedIp, true, substationLabel, ipLoginEdit, ipPasswordEdit, ipMultipleCheckBox);
    });

    QLabel *remotePathLabel = new QLabel("Віддалений шлях: ");
    QLineEdit *remotePathEdit = new QLineEdit();
    QString struct_id = rowData[7];
    QSqlQuery checkPathQuery;
    checkPathQuery.prepare("SELECT remote_path FROM [ReconDB].[dbo].[FTP_Directories] WHERE struct_id = :struct_id");
    checkPathQuery.bindValue(":struct_id", struct_id);

    if (checkPathQuery.exec() && checkPathQuery.next()) {
        remotePathEdit->setText(rowData[5]);
    }

    QPushButton *saveButton = new QPushButton("Зберегти", currentFactoryDialog);
    QPushButton *deleteButton = new QPushButton("Видалити", currentFactoryDialog);

    layout->addWidget(ipAddressLabel);

    // Создаем горизонтальный layout для поля ввода IP и ComboBox
    QHBoxLayout *ipLayout = new QHBoxLayout;
    ipLayout->addWidget(ipAddressEdit);         // Поле ввода IP
    ipLayout->addWidget(ipAddressComboBox);     // ComboBox с IP адресами
    layout->addLayout(ipLayout);

    layout->addWidget(substationLabel);

    layout->addWidget(ipLoginLabel);
    layout->addWidget(ipLoginEdit);
    layout->addWidget(ipPasswordLabel);

    // Размещаем поле пароля и чекбокс горизонтально
    QHBoxLayout *passwordLayout = new QHBoxLayout;
    passwordLayout->addWidget(ipPasswordEdit);
    passwordLayout->addWidget(showPasswordCheckBox);
    layout->addLayout(passwordLayout);

    layout->addWidget(remotePathLabel);
    layout->addWidget(remotePathEdit);

    QHBoxLayout *multipleParamLayout = new QHBoxLayout;
    multipleParamLayout->addWidget(ipMultipleLabel);
    multipleParamLayout->addWidget(ipMultipleCheckBox);
    layout->addLayout(multipleParamLayout);

    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(saveButton);
    buttonsLayout->addWidget(deleteButton);
    deleteButton->setVisible(!ipLoginEdit->text().isEmpty());
    layout->addLayout(buttonsLayout);

    currentFactoryDialog->setLayout(layout);

    connect(showPasswordCheckBox, &QCheckBox::checkStateChanged, this, [=](int state)
    {
        if (state == Qt::Checked)
        {
            ipPasswordEdit->setEchoMode(QLineEdit::Normal);     // Показывать пароль
        }
        else
        {
            ipPasswordEdit->setEchoMode(QLineEdit::Password);   // Скрывать пароль
        }
    });

    connect(saveButton, &QPushButton::clicked, this, [=]()
    {
        updateIpAssignment(rowData, ipAddressEdit, ipLoginEdit, ipPasswordEdit, remotePathEdit, ipMultipleCheckBox);
        currentFactoryDialog->accept();
        LoadServiceTree();
    });

    connect(deleteButton, &QPushButton::clicked, this, [=]()
    {
        QString unit_id = rowData[0];
        DeleteAddress(unit_id, ipAddressEdit);
        currentFactoryDialog->accept();
        LoadServiceTree();
    });
    currentFactoryDialog->exec();
}
bool MainWindow::CheckEmptyFieldsFactoryDialog(QLineEdit *ipAddressEdit, QLineEdit *ipLoginEdit,
                                               QLineEdit *ipPasswordEdit, QLineEdit *remotePathEdit){
    QString ipAddress = ipAddressEdit->text();
    QString ipLogin = ipLoginEdit->text();
    QString ipPassword = ipPasswordEdit->text();
    QString remotePath = remotePathEdit->text();

    // Проверка на пустые поля
    bool hasError = false;
    bool hasIpError = false;

    // Проверка корректности IP-адреса с помощью регулярного выражения
    QRegularExpression ipRegex(R"(^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$)");

    if (ipAddress.isEmpty() || !ipRegex.match(ipAddress).hasMatch()) {
        ipAddressEdit->setStyleSheet("border: 1px solid red;");
        hasIpError = true;
    } else {
        ipAddressEdit->setStyleSheet("");
    }

    if (ipLogin.isEmpty()) {
        ipLoginEdit->setStyleSheet("border: 1px solid red;");
        hasError = true;
    } else {
        ipLoginEdit->setStyleSheet("");
    }

    if (ipPassword.isEmpty()) {
        ipPasswordEdit->setStyleSheet("border: 1px solid red;");
        hasError = true;
    } else {
        ipPasswordEdit->setStyleSheet("");
    }

    if(remotePath.isEmpty()){
        remotePathEdit->setStyleSheet("border: 1px solid red;");
        hasError = true;
    } else {
        remotePathEdit->setStyleSheet("");
    }

    if (hasError)
    {
        // Показать сообщение об ошибке, если есть пустые поля
        QMessageBox::warning(currentFactoryDialog, "Помилка", "Будь ласка, заповніть всі поля");
        return false;
    }
    else if(hasIpError)
    {
        QMessageBox::warning(currentFactoryDialog, "Помилка", "Будь ласка, перевірте правильність айпі адреси");
        return false;
    }
    return true;
}

QList<QVariantMap> MainWindow::getIpRecords(const QString &ip){
    QList<QVariantMap> records;

    QSqlQuery query;
    query.prepare("SELECT unit_id, isMultiple FROM [ReconDB].[dbo].[FTP_servers] "
                                "WHERE [IP_addr] = :ip");
    query.bindValue(":ip", ip);

    if (!query.exec()) {
        QMessageBox::critical(this, "Помилка", "Помилка перевірки на дублі IP: " + query.lastError().text());
        return {};
    }

    while (query.next()) {
        QVariantMap record;
        record["unit_id"] = query.value("unit_id");
        record["isMultiple"] = query.value("isMultiple");
        records.append(record);
    }
    qDebug() << "records: " << records;
    return records;
}

void MainWindow::unmarkAsMultipleAndCleanOthers(const QString &ip, int currentUnitId) {
    QSqlQuery query;

    query.prepare(R"(
        UPDATE [ReconDB].[dbo].[FTP_servers]
        SET
            unit_id = CASE
                WHEN unit_id IS NOT NULL AND unit_id != :currentUnitId THEN NULL
                ELSE unit_id
            END,
            isMultiple = 0
        WHERE IP_addr = :ip
    )");

    query.bindValue(":ip", ip);
    query.bindValue(":currentUnitId", currentUnitId);

    if (!query.exec()) {
        qDebug() << "Error in combined update:" << query.lastError().text();
    }
}


bool hasUnitId(const QList<QVariantMap> &records, int unitIdToFind) {
    for (const QVariantMap &record : records) {
        if (!record["unit_id"].isNull() && record["unit_id"].toInt() == unitIdToFind) {
            return true;
        }
    }
    return false;
}

bool hasEmptyOrZeroUnitId(const QList<QVariantMap> &records) {
    for (const QVariantMap &record : records) {
        QVariant unitId = record.value("unit_id");
        if (unitId.isNull() || unitId.toInt() == 0) {
            return true;
        }
    }
    return false;
}

void bindIpQueryValues(QSqlQuery& query, const QVariant& unitId, const QString& ipAddr, const QString& login,
                       const QString& password, int status, const QVariant& previousUnit, bool isMultiple) {
    query.bindValue(":unitId", unitId);
    query.bindValue(":ipAddress", ipAddr);
    query.bindValue(":ipLogin", login);
    query.bindValue(":ipPassword", password);
    query.bindValue(":status", status);
    query.bindValue(":previousUnit", previousUnit);
    query.bindValue(":isMultipleIp", isMultiple ? 1 : 0);
}

bool handleNewIpInsert(bool hasEmptyUnit, const QVariant& unitId, const QString& ipAddr, const QString& login,
                       const QString& password, int status, const QVariant& previousUnit, bool isMultiple) {
    QSqlQuery query;

    if (hasEmptyUnit) {
        query.prepare(R"(
            WITH FirstMatchingRow AS (
                SELECT TOP 1 *
                FROM [ReconDB].[dbo].[FTP_servers]
                WHERE unit_id IS NULL AND IP_addr = :ipAddress
            )
            UPDATE FirstMatchingRow
            SET
                unit_id = :unitId,
                IP_addr = :ipAddress,
                login = :ipLogin,
                password = :ipPassword,
                status = :status,
                previous_unit = :previousUnit,
                isMultiple = :isMultipleIp
        )");
    } else {
        query.prepare("INSERT INTO [ReconDB].[dbo].[FTP_servers] "
                      "(unit_id, IP_addr, login, password, status, previous_unit, isMultiple) "
                      "VALUES(:unitId, :ipAddress, :ipLogin, :ipPassword, :status, :previousUnit, :isMultipleIp)");
    }

    bindIpQueryValues(query, unitId, ipAddr, login, password, status, previousUnit, isMultiple);

    if (!query.exec()) {
        QMessageBox::critical(nullptr, "Помилка", "Помилка додаванні IP-адреси: " + query.lastError().text());
        return false;
    }

    QSqlQuery updateMultipleQuery;
    updateMultipleQuery.prepare("UPDATE [ReconDB].[dbo].[FTP_servers] "
                                "SET isMultiple = :isMultipleIp "
                                "WHERE IP_addr = :ipAddress");

    updateMultipleQuery.bindValue(":isMultipleIp", isMultiple ? 1 : 0);
    updateMultipleQuery.bindValue(":ipAddress", ipAddr);

    if (!updateMultipleQuery.exec()) {
        QMessageBox::critical(nullptr, "Помилка", "Помилка при оновленні isMultiple для всіх записів з IP: " + updateMultipleQuery.lastError().text());
        return false;
    }

    return true;
}

bool handleSingleIpUpdate(const QVariantMap & record, const QVariant& unitId, const QString& ipAddr,
                          const QString& ipFromTable, const QString& login, const QString& password,
                          int status, const QVariant& previousUnit, bool isMultiple) {
    QSqlQuery query;

    if (record["unit_id"].isNull()) {
        query.prepare("UPDATE [ReconDB].[dbo].[FTP_servers] "
                      "SET unit_id = :unitId, login = :ipLogin, password = :ipPassword, "
                      "status = :status, previous_unit = :previousUnit, isMultiple = :isMultipleIp "
                      "WHERE IP_addr = :ipAddress");

        bindIpQueryValues(query, unitId, ipAddr, login, password, status, previousUnit, isMultiple);
    } else if (record["unit_id"].toInt() != unitId.toInt()) {
        QMessageBox::warning(nullptr, "Попередження",
                             "Сервер з IP '" + ipAddr + "' вже прив'язаний до іншого об'єкту. "
                                                        "Один сервер не може бути прив'язаний до різних об'єктів без статусу мульти-айпі.");
        return false;
    } else {
        QString updateStr = "UPDATE [ReconDB].[dbo].[FTP_servers] SET "
                            "login = :ipLogin, password = :ipPassword, isMultiple = :isMultipleIp, status = :status";

        if (ipAddr == ipFromTable)
            updateStr += " WHERE IP_addr = :ipAddress";
        else
            updateStr += ", IP_addr = :ipAddress WHERE unit_id = :unitId";

        query.prepare(updateStr);
        query.bindValue(":ipLogin", login);
        query.bindValue(":ipPassword", password);
        query.bindValue(":status", status);
        query.bindValue(":isMultipleIp", isMultiple);
        query.bindValue(":ipAddress", ipAddr);

        if (ipAddr != ipFromTable)
            query.bindValue(":unitId", unitId);
    }

    if (!query.exec()) {
        QMessageBox::critical(nullptr, "Помилка", "Помилка оновленні IP-адреси: " + query.lastError().text());
        return false;
    }

    if (status != 1) {
        QMessageBox::warning(nullptr, "Підключення до сервера", "З’єднання з сервером не було встановлено.");
    }

    return true;
}

bool MainWindow::handleMultipleIpUpdate(bool isMultiple, bool currentMultiple, int numUnits, const QString& ipFromTable,
                            const QVariant& unitId, const QString& ipAddr, const QString& login,
                            const QString& password, int status, const QVariant& previousUnit) {
    if (isMultiple && !currentMultiple && numUnits > 1) {
        QMessageBox::StandardButton reply = QMessageBox::question(nullptr, "Попередження",
                                                                  "Ви впевнені, що хочете прибрати статус 'мульти-айпі'? Усі інші прив’язки цього айпі будуть повністю видалені.",
                                                                  QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            unmarkAsMultipleAndCleanOthers(ipFromTable, unitId.toInt());
        }
        return false;
    }

    QSqlQuery query;
    query.prepare("UPDATE [ReconDB].[dbo].[FTP_servers] "
                  "SET login = :ipLogin, password = :ipPassword, status = :status, "
                  "previous_unit = :previousUnit, isMultiple = :isMultipleIp "
                  "WHERE IP_addr = :ipAddress AND unit_id = :unitId");

    bindIpQueryValues(query, unitId, ipAddr, login, password, status, previousUnit, currentMultiple);

    if (!query.exec()) {
        QMessageBox::critical(nullptr, "Помилка", "Помилка оновленні IP-адреси: " + query.lastError().text());
        return false;
    }

    return true;
}

void MainWindow::updateIpAssignment(const QStringList &rowData, QLineEdit *ipAddressEdit,
                               QLineEdit *ipLoginEdit, QLineEdit *ipPasswordEdit,
                               QLineEdit *remotePathEdit, QCheckBox *isMultipleIpCheckBox){
    // Получаем значения из полей
    QString ipAddress = ipAddressEdit->text();
    QString ipLogin = ipLoginEdit->text();
    QString ipPassword = ipPasswordEdit->text();
    QString remotePath = remotePathEdit->text();
    bool currentIpIsMultiple = isMultipleIpCheckBox->isChecked();
    int status = 0;

    if(!CheckEmptyFieldsFactoryDialog(ipAddressEdit,ipLoginEdit,ipPasswordEdit,remotePathEdit)){
        return;
    }

    // Проверка наличия IP-адреса в базе данных (по айди из таблицы объектов)
    int unitId_fromTable = rowData[0].toInt();
    QString unitFromTable = rowData[2];
    QString ipFromTable = rowData[4];

    QList<QVariantMap> records = getIpRecords(ipAddress);
    qDebug() << "1 ";
    bool ipExists = !records.isEmpty();
     qDebug() << "2 ";
    bool ipWithUnitExists = hasUnitId(records, unitId_fromTable);
      qDebug() << "3 ";
    bool isMultiple;
    int numRealUnits;

    if(ipExists){

    isMultiple = records.first()["isMultiple"].toBool();
       qDebug() << "4 ";
    numRealUnits = std::count_if(records.begin(), records.end(), [](const auto &r) {
        return !r["unit_id"].isNull();
    });

    }
    qDebug() << "5 ";

    qDebug() << "ipExists " << ipWithUnitExists;
    qDebug() << "isMultiple " << isMultiple;
    qDebug() << "currentIpIsMultiple " << currentIpIsMultiple;
    qDebug() << "numRealUnits" << numRealUnits;

    if(!currentIpIsMultiple && numRealUnits >= 1 && ipFromTable.isEmpty()){
        QMessageBox::warning(this, "Помилка прив'язки", "Цей айпі вже прив'язан, до іншого об'єкту та він не має статуса 'мульти-айпі'. \n"
                                                        "Встановіть галочку 'Збирає с декілької об'єктів?' або спробуйте змінити айпі на інший.");
        return;
    }

    // Проверка подключения по введённым данным
    if (CheckFtpConnection(ipAddress, remotePath, ipLogin, ipPassword)) {
        status = 1;
    } else {
        status = 2;
    }

    if(!ipWithUnitExists){
        qDebug() << "IP was not exists";

        handleNewIpInsert(hasEmptyOrZeroUnitId(records),
                          unitId_fromTable, ipAddress, ipLogin, ipPassword,
                          status, unitFromTable, currentIpIsMultiple);
    } else {
        qDebug() << "IP was exists";
        if(!isMultiple){
            qDebug() << "IP is not Multiple";
            handleSingleIpUpdate(records.first(), unitId_fromTable, ipAddress,
                                 ipFromTable, ipLogin, ipPassword,
                                 status, unitFromTable, currentIpIsMultiple);
        } else {
            qDebug() << "IP is Multiple";
            handleMultipleIpUpdate(isMultiple, currentIpIsMultiple, numRealUnits,
                                   ipFromTable, unitId_fromTable, ipAddress,
                                   ipLogin, ipPassword, status, unitFromTable);
        }
    }
}

void MainWindow::DeleteAddress(QString unit_id, QLineEdit *ipAddressEdit)
{
    QString ipAddress = ipAddressEdit->text();

    if (ipAddress.isEmpty())
    {
        qDebug() << "Не указан IP для удаления!";
        return;
    }

    // Пример удаления данных из базы данных
    QSqlQuery query;
    query.prepare("UPDATE [ReconDB].[dbo].[FTP_servers] "
                  "SET [unit_id] = NULL "
                  "WHERE [IP_addr] = :ip AND [unit_id] = :unit_id");
    query.bindValue(":ip", ipAddress);
    query.bindValue(":unit_id", unit_id);

    if (query.exec())
    {
        qDebug() << "Данные успешно удалены!";
    }
    else
    {
        qDebug() << "Ошибка удаления данных: " << query.lastError().text();
    }
}

// Уничтожение объекта "Мейн-окна"(Деструктор)
MainWindow::~MainWindow()
{
    DisconnectFromDatabase();  // Отключение от базы данных перед уничтожением объекта
    delete ui;
}
