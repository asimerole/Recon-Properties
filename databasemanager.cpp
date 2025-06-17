#include "databasemanager.h"

DatabaseManager::DatabaseManager() {}

bool DatabaseManager::ConnectToDatabase(const QString &dbAddress, const QString &dbName,
                                        const QString &username, const QString &password, const QString &instanceOrPort)
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
                      .arg(serverAddress, dbName, username, password);
    DBConnection.setDatabaseName(dsn);

    if (!DBConnection.open()) {
        return false;
    }

    return true;
}

QSqlDatabase DatabaseManager::getConnection()
{
    return DBConnection;
}

void DatabaseManager::DisconnectFromDatabase()
{
    if (DBConnection.isOpen())
    {
        DBConnection.close();
    }
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);  // Remove connection
}
