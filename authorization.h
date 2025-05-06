#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QJsonDocument>
#include <QJsonObject>

namespace Ui {
class Authorization;
}

class Authorization : public QDialog
{
    Q_OBJECT

public:
    explicit Authorization(QWidget *parent = nullptr);
    ~Authorization();

    QString getUsername() const;
    QString getPassword() const;
    QString getDBAddress() const;
    QString getDBName() const;

private slots:
    void on_authButton_clicked();
    void on_checkBox_toggled(bool checked);

signals:
    void authorizationSuccessful();

private:
    Ui::Authorization *ui;
    QSqlDatabase DBConnection;
};

#endif // AUTHORIZATION_H
