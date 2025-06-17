#include "authorization.h"
#include "./ui_authorization.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QTimer>
#include <QElapsedTimer>

Authorization::Authorization(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Authorization)
{
    ui->setupUi(this);
    setWindowTitle("Авторізація");
}

QString Authorization::getUsername() const
{
    return ui->login->text();
}

QString Authorization::getPassword() const
{
    return ui->pass->text();
}

QString Authorization::getDBAddress() const
{
    return ui->dbAddress->text();
}

QString Authorization::getDBName() const
{
    return ui->dbName->text();
}

// Function for checking DB parameters and authorization
void Authorization::on_authButton_clicked()
{
    QString inputUsername = getUsername();
    QString inputPassword = getPassword();
    QString inputDBAddress = getDBAddress();
    QString inputDBName = getDBName();

    // Check for empty fields
    if (inputUsername.isEmpty() || inputPassword.isEmpty() || inputDBAddress.isEmpty() || inputDBName.isEmpty()) {
        if (inputUsername.isEmpty()) {
            ui->login->setStyleSheet("border: 1px solid red;");
        } else {
            ui->login->setStyleSheet("");
        }

        if (inputPassword.isEmpty()) {
            ui->pass->setStyleSheet("border: 1px solid red;");
        } else {
            ui->pass->setStyleSheet("");
        }

        if (inputDBAddress.isEmpty()) {
            ui->dbAddress->setStyleSheet("border: 1px solid red;");
        } else {
            ui->dbAddress->setStyleSheet("");
        }
        if (inputDBName.isEmpty()) {
            ui->dbName->setStyleSheet("border: 1px solid red;");
        } else {
            ui->dbName->setStyleSheet("");
        }

        ui->authErrorLabel->setText("Будь ласка, заповніть всі поля");
        ui->authErrorLabel->setStyleSheet("color: red;");
        return;
    }

    QElapsedTimer timer;
    timer.start();

    DBConnection = QSqlDatabase::addDatabase("QODBC");
    QString serverName = inputDBAddress;    // Server name
    QString databaseName = inputDBName;     // Base name
    QString username = inputUsername;       // server user
    QString password = inputPassword;       // password for user
    QString dsn = QString("Driver={SQL Server};Server=%1;Database=%2;UID=%3;PWD=%4;Encrypt=no;TrustServerCertificate=yes;")
                      .arg(serverName).arg(databaseName).arg(username).arg(password);
    DBConnection.setDatabaseName(dsn);

    QTimer *connectionTimer = new QTimer(this);
    connectionTimer->setSingleShot(true);

    connect(connectionTimer, &QTimer::timeout, this, [this, &timer]() {
        if (!DBConnection.isOpen()) {
            ui->authErrorLabel->setText("Адрес бази вказано невірно");
            ui->authErrorLabel->setStyleSheet("color: red;");
            ui->dbAddress->setStyleSheet("border: 1px solid red;");
        }
    });

    connectionTimer->start(5000); // Checking in 5 seconds

    if (DBConnection.open())
    {
        connectionTimer->stop(); // If the connection is established, we stop the timer

        // Creating a JSON string for database
        QJsonObject json;
        json["login"] = username;
        json["password"] = password;
        json["nameDB"] = databaseName;
        json["addressDB"] = serverName;
        QJsonDocument doc(json);
        QString jsonString = QString::fromUtf8(doc.toJson());

        // Executing SQL query for update
        QSqlQuery query;
        query.prepare("UPDATE [ReconDB].[dbo].[access_settings] SET [value] = :value WHERE [name] = :name");
        query.bindValue(":value", jsonString);
        query.bindValue(":name", "database");
        query.exec();

        ui->authErrorLabel->clear();    // Clearing the error message
        emit authorizationSuccessful(); // We send a signal about successful authorization
        accept();                       // Close the authorization window
    }
    else if (timer.elapsed() < 5000)
    {
        // We display a message about an incorrect login or password
        ui->authErrorLabel->setText("Логін або пароль указано невірно");

        // Additionally, you can clear the login and password fields for re-entry.
        ui->pass->clear();
        ui->dbAddress->setStyleSheet("");
        ui->login->setStyleSheet("border: 1px solid red;");
        ui->pass->setStyleSheet("border: 1px solid red;");
    }
}

// Checkbox to show/hide password
void Authorization::on_checkBox_toggled(bool checked)
{
    if (checked) {
        ui->pass->setEchoMode(QLineEdit::Normal);
    } else {
        ui->pass->setEchoMode(QLineEdit::Password);
    }
}

Authorization::~Authorization()
{
    delete ui;
}
