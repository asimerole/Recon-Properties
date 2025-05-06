#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCryptographicHash>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QStandardPaths>
#include <QMessageBox>
#include <QCheckBox>
#include <QComboBox>
#include <QFileDialog>
#include <QDir>
#include <QDialog>
#include <QInputDialog>
#include <QFile>
#include <QTextStream>
#include <QTextEdit>
#include <QThread>
#include <QListWidget>
#include <QListWidgetItem>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTreeWidget>
#include <QTableWidget>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QFormLayout>
// For FTP
#include <curl/curl.h>
#include <QtConcurrent/QtConcurrent>
// For Crypto
#include <QByteArray>
#include <QMessageAuthenticationCode>
#include <QDebug>

#include <openssl/evp.h>
#include <openssl/rand.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(const QString &dbAddress, const QString &dbName, const QString &username, const QString &password, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Создание конфиг файла
    void CreateConfigFile();

    // Шифорвание конфиг файла
    bool encryptDataToFile(const QByteArray& data, const QString& filePath, const unsigned char* key, const unsigned char* iv);

    // Добавления пользователя в Базу
    void AddUserToDB();

    // Оьновление параметров пользователя
    void UpdateUser();

    // Обновление присвоенных объектов юзеру
    void updateSelectedObjects(int userRow);

    // Удаление юзера
    void DeleteUser();

    // Выбор объектов
    void SelectObjects();

    // Загрузка таблицы пользователей (Вкладка 2)
    void LoadUsers();

    // Загрузка таблицы фтп серверов (Вкладка 3)
    void LoadServiceTree();

    // Изменение пароля для пользователя
    void HandleChangePassword(int userID);

    // Загрузка таблицы с настрйоками (Вкладка 1)
    void LoadSettings();

    // Обновления данных о параметрах в БД
    void OpenEditSettingsDialog();

    // Создание диалогового окна для пользователя
    QDialog* CreateUserDialog(QLineEdit*& userLoginEdit, QLineEdit*& userWorkPosition, QComboBox*& userTypeComboBox,
                              QCheckBox*& userMailingDataCheck, QPushButton*& objectsButton,
                              QPushButton*& actionButton, QLabel*& errorLabel);


    // Сворачивание объектов в 1 строку
    void toggleRowVisibility(int parentRow, int parentColumn, bool collapse);

    // Добавление текста с кнопкой в ячейку
    void AddTextWithButton(int row, int column, const QString &text);

    //
    bool CheckObjectsSelection(const QString& userType);

    // Заполнение объектов админу
    void FillAdminObjects(int userID);

    // Заполнение объектов пользователю
    void FillUserObjects(int userID);

    // Обновление статуса активности пользователя
    void UpdateUserStatus(int userID, bool isActive);

    // Филтрование юзеров по имени (через виджет ввода LineEdit)
    void FilterUsers(const QString &searchText);

    // Слот для выбора строки в таблице серверов ФТП
    void OnFactorySelected(QTableWidgetItem *item);

    // Открытие диалогового окна при выборе ячейки из таблицы серверов ФТП
    void OpenFactoryDialog(const QStringList &rowData);

    // Создание диалогового окна для таблицы настройки параметров
    QDialog* createDialog(const QString &name, QString &value);

    // Установка параметров для Почтового модуля
    void setupMailSettings(QVBoxLayout *layout, const QString &value, QPushButton *saveButton);

    // Установка параметров для модуля Вандрайв
    void setupOnedriveSettings(QVBoxLayout *layout, const QString &value);

    // Установка параметров
    void setupRootDirectorySettings(QVBoxLayout *layout, const QString &value);

    // Установка параметров по умолчанию (для всего остального)
    void setupDefaultSettings(QVBoxLayout *layout, QString &value);

    // Сохранение параметров в базу (слот для кнопки сохранения)
    bool saveSettings(const QString &name);

    // Проверка подключения к серверу по фтп
    bool CheckFtpConnection(const QString &ipAddress, const QString &remoteFolder, const QString &username,
                            const QString &password);

    // Проверка сузествования каталога на удалённом сервере
    bool CheckFtpFolderExists(const QString &ipAddress, const QString &remoteFolder, const QString &username,
                              const QString &password);

    // Обновление статуса активности сервера
    void UpdateFactoryStatus(const QString& ipAddress, bool isActive);

    // Обновление статуса для четырёхзначных папок(регистраторов)
    void UpdateFourDigitsStatus(const QString& remotePath, bool isTrue);

    // Обновление параметров айпи
    void UpdateIpParams(int &unit_id, QString &ipAddress, QString &prevIP, QString &ipLogin, QString &ipPassword, QString &struct_id,
                        QString &remotePath, QString &localPath, QString &previousUnit, bool isMultiple);

    // Проверка полей в окне настройки айпи сервера
    bool CheckEmptyFieldsFactoryDialog(QLineEdit *ipAddressEdit, QLineEdit *ipLoginEdit,
                                       QLineEdit *ipPasswordEdit, QLineEdit *remotePathEdit);

    // Возврат записей из базы о айпи
    QList<QVariantMap> getIpRecords(const QString &ip);

    // Работа с базой для мульти айпи
    bool handleMultipleIpUpdate(bool isMultiple, bool currentMultiple, int numUnits, const QString& ipFromTable,
                                const QVariant& unitId, const QString& ipAddr, const QString& login,
                                const QString& password, int status, const QVariant& previousUnit);

    void loadIpCredentials(const QString &ip, bool updateSubstationLabel, QLabel *substationLabel, QLineEdit *ipLoginEdit, QLineEdit *ipPasswordEdit, QCheckBox *ipMultipleCheckBox);

    // Сохранение айпи сервера (привязка айпи к объекту)
    void updateIpAssignment(const QStringList &rowData, QLineEdit *ipAddressEdit,
                    QLineEdit *ipLoginEdit, QLineEdit *ipPasswordEdit, QLineEdit *remotePathEdit, QCheckBox *isMultipleIpCheckBox);

    // Видалення статусу мулти-айпи
    void unmarkAsMultipleAndCleanOthers(const QString &ip, int currentUnitId);

    // Удаление адресса (отвзяка айпи от объекта)
    void DeleteAddress(QString unit_id, QLineEdit *ipAddressEdit);

    // Вставка каталога на удалённом сервере (запускается в основном для всех строк в таблице списка серверов ФТП)
    void InsertDirValue(QString struct_id, QString remote_path, QString local_path);

    // Заполение пустых полей (чаще всего для удалённых каталогов)
    void FillMissingData();

    // Включение и выключение групп
    void updateGroupSetting(bool checked);



private:
    // Подключение к базе
    bool ConnectToDatabase(const QString &dbAddress, const QString &databaseName, const QString &username, const QString &password, const QString &instanceOrPort);

    // Отключение от базы
    void DisconnectFromDatabase();

    Ui::MainWindow *ui;
    QSqlDatabase DBConnection;
    QStringList selectedObjects;

    QDialog *currentFactoryDialog = nullptr;

    QLineEdit *smtpEdit;                                // Поле для ввода SMTP сервера
    QLineEdit *emailSenderEdit;                         // Поле для ввода почты отправителя
    QLineEdit *nameSenderEdit;                          // Поле для ввода имени отправителя
    QTextEdit *msgTemplate;                             // Поле для ввода шаблона сообщения
    QCheckBox *sslCheck;                                // Галочка для включения SSL
    QCheckBox *authCheck;                               // Галочка для включения Аунтефикации
    QLineEdit *authLoginEdit;                           // Поле для ввода Логина в случае Аунтефикации
    QLineEdit *authPasswordEdit;                        // Поле для ввода Пароля в случае Аунтефикации
    QLineEdit *pathEdit;                                // Поле для ввода путя к папке OneDrive
    QLineEdit *monthsEdit;                              // Поле для ввода кол-ва месяцев хранения
    QLineEdit *rootPathEdit;                            // Поле для ввода корневой папки
    QLineEdit *timeValueEdit;                           // Поле для ввода времени цикла интеграции
    QLineEdit *portEdit;                                    // Поле для ввода порта сервера

};

#endif // MAINWINDOW_H
