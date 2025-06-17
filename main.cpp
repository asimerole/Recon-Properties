#include <QApplication>
#include <QIcon>
#include "authorization.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/images/icon.ico"));

    // Creating a login window
    Authorization auth;

    // Show the authorization window and wait for the result
    if (auth.exec() == QDialog::Accepted) {
        // After successful authorization, we receive data and pass it to MainWindow
        QString username = auth.getUsername();
        QString password = auth.getPassword();
        QString dbAddress = auth.getDBAddress();
        QString dbName = auth.getDBName();

        MainWindow w(dbAddress, dbName, username, password);
        w.show(); // We show the main window only after successful authorization
        return a.exec();
    }

    return 0; // The program will terminate if authorization fails.
}
