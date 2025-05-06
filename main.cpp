#include <QApplication>
#include <QIcon>
#include "authorization.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/images/icon.ico"));

    // Создание окна авторизации
    Authorization auth;

    // Показать окно авторизации и ждать результата
    if (auth.exec() == QDialog::Accepted) {
        // После успешной авторизации получаем данные и передаем их в MainWindow
        QString username = auth.getUsername();
        QString password = auth.getPassword();
        QString dbAddress = auth.getDBAddress();
        QString dbName = auth.getDBName();

        MainWindow w(dbAddress, dbName, username, password);
        w.show(); // Показываем главное окно только после успешной авторизации
        return a.exec();
    }

    return 0; // Программа завершится, если авторизация не удалась
}
