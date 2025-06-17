#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QMessageBox>
#include <QWidget>

class DatabaseManager
{
public:
    DatabaseManager();

    // Connection to Database
    bool ConnectToDatabase(const QString& adress, const QString& name, const QString& login, const QString& password,const QString &instanceOrPort);

    // Disconnect from Database
    void DisconnectFromDatabase();

    QSqlDatabase getConnection();

private:
    QSqlDatabase DBConnection;
};

#endif // DATABASEMANAGER_H
