#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCryptographicHash>
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

#include "databasemanager.h"

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
    // Creating a config file
    void CreateConfigFile();

    // Encrypting config file
    bool encryptDataToFile(const QByteArray& data, const QString& filePath, const unsigned char* key, const unsigned char* iv);

    // Adding a user to the Database
    void AddUserToDB();

    // Updating user parameters
    void UpdateUser();

    // Updating objects assigned to a user
    void updateSelectedObjects(int userRow);

    // Deleting a user
    void DeleteUser();

    // Selecting objects
    void SelectObjects();

    // Sorting connector
    void onHeaderClicked(int logicalIndex);

    // Loading the Users Table (Tab 2)
    void LoadUsers();

    // Loading FTP Servers Table (Tab 3)
    void LoadServiceTree();

    // Change password for user
    void HandleChangePassword(int userID);

    // Loading the settings table (Tab 1)
    void LoadSettings();

    // Updates to parameter data in the database
    void OpenEditSettingsDialog();

    // Creating a dialog box for the user
    QDialog* CreateUserDialog(QLineEdit*& userLoginEdit, QLineEdit*& userWorkPosition, QComboBox*& userTypeComboBox,
                              QCheckBox*& userMailingDataCheck, QPushButton*& objectsButton,
                              QPushButton*& actionButton, QLabel*& errorLabel);


    // Collapsing objects into 1 line
    void toggleRowVisibility(int parentRow, int parentColumn, bool collapse);

    // Adding text with a button to a cell
    void AddTextWithButton(int row, int column, const QString &text);

    bool CheckObjectsSelection(const QString& userType);

    // Filling objects for admin
    void FillAdminObjects(int userID);

    // Filling objects for the user
    void FillUserObjects(int userID);

    // Updating user activity status
    void UpdateUserStatus(int userID, bool isActive);

    // Filtering users by name (via QLineEdit input widget)
    void FilterUsers(const QString &searchText);

    // Slot for selecting a row in the FTP server table
    void OnFactorySelected(QTableWidgetItem *item);

    // Opening a dialog box when selecting a cell from the FTP servers table
    void OpenFactoryDialog(const QStringList &rowData);

    // Creating a dialog box for the settings table
    QDialog* createDialog(const QString &name, QString &value);

    // Setting parameters for the Mail module
    void setupMailSettings(QVBoxLayout *layout, const QString &value, QPushButton *saveButton);

    // Setting parameters for the OneDrive module
    void setupOnedriveSettings(QVBoxLayout *layout, const QString &value);

    // Setting parameters
    void setupRootDirectorySettings(QVBoxLayout *layout, const QString &value);

    // Set default settings (for everything else)
    void setupDefaultSettings(QVBoxLayout *layout, QString &value);

    // Saving parameters to the database (slot for the save button)
    bool saveSettings(const QString &name);

    // Checking the connection to the server via FTP
    bool CheckFtpConnection(const QString &ipAddress, const QString &remoteFolder, const QString &username,
                            const QString &password);

    // Checking if a directory exists on a remote server
    bool CheckFtpFolderExists(const QString &ipAddress, const QString &remoteFolder, const QString &username,
                              const QString &password);

    // Updating server activity status
    void UpdateFactoryStatus(const QString& ipAddress, bool isActive);

    // Status update for four-digit folders (registrars)
    void UpdateFourDigitsStatus(const QString& remotePath, bool isTrue);

    // Updating IP parameters
    void UpdateIpParams(int &unit_id, QString &ipAddress, QString &prevIP, QString &ipLogin, QString &ipPassword, QString &struct_id,
                        QString &remotePath, QString &localPath, QString &previousUnit, bool isMultiple);

    // Checking fields in the IP server settings window
    bool CheckEmptyFieldsFactoryDialog(QLineEdit *ipAddressEdit, QLineEdit *ipLoginEdit,
                                       QLineEdit *ipPasswordEdit, QLineEdit *remotePathEdit);

    // Возврат записей из базы о айпи
    QList<QVariantMap> getIpRecords(const QString &ip);

    // Working with a database for multi-ip
    bool handleMultipleIpUpdate(bool isMultiple, bool currentMultiple, int numUnits, const QString& ipFromTable,
                                const QVariant& unitId, const QString& ipAddr, const QString& login,
                                const QString& password, int status, const QVariant& previousUnit);

    void loadIpCredentials(const QString &ip, bool updateSubstationLabel, QLabel *substationLabel, QLineEdit *ipLoginEdit, QLineEdit *ipPasswordEdit, QCheckBox *ipMultipleCheckBox);

    // Saving the server IP (binding the IP to the object)
    void updateIpAssignment(const QStringList &rowData, QLineEdit *ipAddressEdit,
                    QLineEdit *ipLoginEdit, QLineEdit *ipPasswordEdit, QLineEdit *remotePathEdit, QCheckBox *isMultipleIpCheckBox);

    // View multi-IP status
    void unmarkAsMultipleAndCleanOthers(const QString &ip, int currentUnitId);

    // Removing an address (unlinking an IP from an object)
    void DeleteAddress(QString unit_id, QLineEdit *ipAddressEdit);

    // Insert directory on remote server (runs mostly for all rows in FTP server list table)
    void InsertDirValue(QString struct_id, QString remote_path, QString local_path);

    // Filling in empty fields (most often for remote directories)
    void FillMissingData();

    // Turning groups on and off
    void updateGroupSetting(bool checked);



private:
    Ui::MainWindow *ui;
    QStringList selectedObjects;

    // Managers
    DatabaseManager dbManager;

    QDialog *currentFactoryDialog = nullptr;

    QLineEdit *smtpEdit;                                // SMTP server input field
    QLineEdit *emailSenderEdit;                         // Field for entering the sender's email
    QLineEdit *nameSenderEdit;                          // Field for entering the sender's name
    QTextEdit *msgTemplate;                             // Field for entering a message template
    QCheckBox *sslCheck;                                // Checkbox to enable SSL
    QCheckBox *authCheck;                               // Checkbox to enable Authentication
    QLineEdit *authLoginEdit;                           // Login input field in case of Authentication
    QLineEdit *authPasswordEdit;                        // Password input field in case of Authentication
    QLineEdit *pathEdit;                                // Field for entering the path to the OneDrive folder
    QLineEdit *monthsEdit;                              // Field for entering the number of months of storage
    QLineEdit *rootPathEdit;                            // Root folder input field
    QLineEdit *timeValueEdit;                           // Field for entering the integration cycle time
    QLineEdit *portEdit;                                // Server port input field

};

#endif // MAINWINDOW_H
