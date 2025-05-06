/********************************************************************************
** Form generated from reading UI file 'authorization.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTHORIZATION_H
#define UI_AUTHORIZATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Authorization
{
public:
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *labels;
    QLabel *labelLogin;
    QLabel *labelPass;
    QLabel *labelDB;
    QLabel *labelNameDB;
    QVBoxLayout *inputs;
    QLineEdit *login;
    QHBoxLayout *password;
    QLineEdit *pass;
    QCheckBox *checkBox;
    QLineEdit *dbAddress;
    QLineEdit *dbName;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QLabel *authErrorLabel;
    QPushButton *authButton;

    void setupUi(QDialog *Authorization)
    {
        if (Authorization->objectName().isEmpty())
            Authorization->setObjectName("Authorization");
        Authorization->resize(659, 370);
        gridLayout_2 = new QGridLayout(Authorization);
        gridLayout_2->setObjectName("gridLayout_2");
        groupBox = new QGroupBox(Authorization);
        groupBox->setObjectName("groupBox");
        groupBox->setAutoFillBackground(true);
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName("gridLayout");
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout->addItem(verticalSpacer, 0, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 5, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 2, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        labels = new QVBoxLayout();
        labels->setObjectName("labels");
        labelLogin = new QLabel(groupBox);
        labelLogin->setObjectName("labelLogin");

        labels->addWidget(labelLogin);

        labelPass = new QLabel(groupBox);
        labelPass->setObjectName("labelPass");

        labels->addWidget(labelPass);

        labelDB = new QLabel(groupBox);
        labelDB->setObjectName("labelDB");

        labels->addWidget(labelDB);

        labelNameDB = new QLabel(groupBox);
        labelNameDB->setObjectName("labelNameDB");

        labels->addWidget(labelNameDB);


        horizontalLayout->addLayout(labels);

        inputs = new QVBoxLayout();
        inputs->setObjectName("inputs");
        login = new QLineEdit(groupBox);
        login->setObjectName("login");
        login->setMinimumSize(QSize(200, 0));
        login->setMaximumSize(QSize(130, 16777215));

        inputs->addWidget(login);

        password = new QHBoxLayout();
        password->setObjectName("password");
        pass = new QLineEdit(groupBox);
        pass->setObjectName("pass");
        pass->setMinimumSize(QSize(200, 0));
        pass->setMaximumSize(QSize(130, 16777215));
        pass->setEchoMode(QLineEdit::Password);

        password->addWidget(pass);

        checkBox = new QCheckBox(groupBox);
        checkBox->setObjectName("checkBox");

        password->addWidget(checkBox);


        inputs->addLayout(password);

        dbAddress = new QLineEdit(groupBox);
        dbAddress->setObjectName("dbAddress");
        dbAddress->setMaximumSize(QSize(200, 16777215));

        inputs->addWidget(dbAddress);

        dbName = new QLineEdit(groupBox);
        dbName->setObjectName("dbName");
        dbName->setMaximumSize(QSize(200, 16777215));

        inputs->addWidget(dbName);


        horizontalLayout->addLayout(inputs);


        gridLayout->addLayout(horizontalLayout, 2, 1, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName("label");
        QFont font;
        font.setFamilies({QString::fromUtf8("Courier New")});
        font.setPointSize(14);
        font.setBold(true);
        label->setFont(font);
        label->setTabletTracking(false);
        label->setAutoFillBackground(true);
        label->setTextFormat(Qt::MarkdownText);
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 1, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 2, 1, 1);

        authErrorLabel = new QLabel(groupBox);
        authErrorLabel->setObjectName("authErrorLabel");

        gridLayout->addWidget(authErrorLabel, 3, 1, 1, 1);

        authButton = new QPushButton(groupBox);
        authButton->setObjectName("authButton");

        gridLayout->addWidget(authButton, 4, 1, 1, 1);


        gridLayout_2->addWidget(groupBox, 0, 0, 1, 1);


        retranslateUi(Authorization);

        QMetaObject::connectSlotsByName(Authorization);
    } // setupUi

    void retranslateUi(QDialog *Authorization)
    {
        Authorization->setWindowTitle(QCoreApplication::translate("Authorization", "DBMonitor", nullptr));
        groupBox->setTitle(QString());
        labelLogin->setText(QCoreApplication::translate("Authorization", "\320\233\320\276\320\263\321\226\320\275", nullptr));
        labelPass->setText(QCoreApplication::translate("Authorization", "\320\237\320\260\321\200\320\276\320\273\321\214", nullptr));
        labelDB->setText(QCoreApplication::translate("Authorization", "\320\241\320\265\321\200\320\262\320\265\321\200 \320\221\320\224", nullptr));
        labelNameDB->setText(QCoreApplication::translate("Authorization", "\320\206\320\274'\321\217 \320\221\320\224", nullptr));
        checkBox->setText(QString());
        label->setText(QCoreApplication::translate("Authorization", "\320\227\320\260\320\264\320\260\321\202\320\270 \320\277\320\260\321\200\320\260\320\274\320\265\321\202\321\200\320\270 \320\277\321\226\320\264\320\272\320\273\321\216\321\207\320\265\320\275\320\275\321\217", nullptr));
        authErrorLabel->setText(QString());
        authButton->setText(QCoreApplication::translate("Authorization", "\320\237\321\226\320\264\320\272\320\273\321\216\321\207\320\270\321\202\320\270\321\201\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Authorization: public Ui_Authorization {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTHORIZATION_H
