/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QTabWidget *tabWidget;
    QWidget *generalProperties;
    QGridLayout *gridLayout_5;
    QGroupBox *groupBox_12;
    QGridLayout *gridLayout_4;
    QPushButton *saveConfigButton;
    QSpacerItem *horizontalSpacer;
    QTableWidget *settingsTableWidget;
    QWidget *userProperties;
    QGridLayout *gridLayout;
    QGroupBox *groupBox_7;
    QGridLayout *gridLayout_6;
    QLabel *findUserLabel;
    QLineEdit *findUserEdit;
    QTableWidget *userTableWidget;
    QPushButton *deleteUserButton;
    QPushButton *addUserButton;
    QWidget *ftpProperties;
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_7;
    QTableWidget *serviceTreeTableWidget;
    QPushButton *collectionButton;
    QCheckBox *filledParamsCheck;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *refreshFtpTableButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->setWindowModality(Qt::NonModal);
        MainWindow->resize(1168, 652);
        MainWindow->setMinimumSize(QSize(1168, 652));
        MainWindow->setMaximumSize(QSize(16777215, 16777215));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName("gridLayout_2");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setMinimumSize(QSize(1150, 591));
        generalProperties = new QWidget();
        generalProperties->setObjectName("generalProperties");
        gridLayout_5 = new QGridLayout(generalProperties);
        gridLayout_5->setObjectName("gridLayout_5");
        groupBox_12 = new QGroupBox(generalProperties);
        groupBox_12->setObjectName("groupBox_12");
        gridLayout_4 = new QGridLayout(groupBox_12);
        gridLayout_4->setObjectName("gridLayout_4");
        saveConfigButton = new QPushButton(groupBox_12);
        saveConfigButton->setObjectName("saveConfigButton");
        saveConfigButton->setMaximumSize(QSize(200, 16777215));

        gridLayout_4->addWidget(saveConfigButton, 1, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_4->addItem(horizontalSpacer, 1, 2, 1, 1);

        settingsTableWidget = new QTableWidget(groupBox_12);
        settingsTableWidget->setObjectName("settingsTableWidget");

        gridLayout_4->addWidget(settingsTableWidget, 0, 0, 1, 3);


        gridLayout_5->addWidget(groupBox_12, 0, 0, 1, 1);

        tabWidget->addTab(generalProperties, QString());
        userProperties = new QWidget();
        userProperties->setObjectName("userProperties");
        gridLayout = new QGridLayout(userProperties);
        gridLayout->setObjectName("gridLayout");
        groupBox_7 = new QGroupBox(userProperties);
        groupBox_7->setObjectName("groupBox_7");
        gridLayout_6 = new QGridLayout(groupBox_7);
        gridLayout_6->setObjectName("gridLayout_6");
        findUserLabel = new QLabel(groupBox_7);
        findUserLabel->setObjectName("findUserLabel");
        findUserLabel->setMaximumSize(QSize(110, 16777215));

        gridLayout_6->addWidget(findUserLabel, 1, 0, 1, 1);

        findUserEdit = new QLineEdit(groupBox_7);
        findUserEdit->setObjectName("findUserEdit");
        findUserEdit->setMaximumSize(QSize(150, 16777215));

        gridLayout_6->addWidget(findUserEdit, 1, 1, 1, 1);

        userTableWidget = new QTableWidget(groupBox_7);
        userTableWidget->setObjectName("userTableWidget");

        gridLayout_6->addWidget(userTableWidget, 0, 0, 1, 4);

        deleteUserButton = new QPushButton(groupBox_7);
        deleteUserButton->setObjectName("deleteUserButton");

        gridLayout_6->addWidget(deleteUserButton, 1, 3, 1, 1);

        addUserButton = new QPushButton(groupBox_7);
        addUserButton->setObjectName("addUserButton");

        gridLayout_6->addWidget(addUserButton, 1, 2, 1, 1);


        gridLayout->addWidget(groupBox_7, 0, 0, 1, 1);

        tabWidget->addTab(userProperties, QString());
        ftpProperties = new QWidget();
        ftpProperties->setObjectName("ftpProperties");
        gridLayout_3 = new QGridLayout(ftpProperties);
        gridLayout_3->setObjectName("gridLayout_3");
        groupBox_4 = new QGroupBox(ftpProperties);
        groupBox_4->setObjectName("groupBox_4");
        groupBox_4->setMaximumSize(QSize(16777215, 125122));
        gridLayout_7 = new QGridLayout(groupBox_4);
        gridLayout_7->setObjectName("gridLayout_7");
        serviceTreeTableWidget = new QTableWidget(groupBox_4);
        serviceTreeTableWidget->setObjectName("serviceTreeTableWidget");

        gridLayout_7->addWidget(serviceTreeTableWidget, 0, 0, 1, 5);

        collectionButton = new QPushButton(groupBox_4);
        collectionButton->setObjectName("collectionButton");

        gridLayout_7->addWidget(collectionButton, 1, 1, 1, 1);

        filledParamsCheck = new QCheckBox(groupBox_4);
        filledParamsCheck->setObjectName("filledParamsCheck");

        gridLayout_7->addWidget(filledParamsCheck, 1, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_7->addItem(horizontalSpacer_2, 1, 4, 1, 1);

        refreshFtpTableButton = new QPushButton(groupBox_4);
        refreshFtpTableButton->setObjectName("refreshFtpTableButton");
        refreshFtpTableButton->setAutoDefault(false);

        gridLayout_7->addWidget(refreshFtpTableButton, 1, 3, 1, 1);


        gridLayout_3->addWidget(groupBox_4, 0, 0, 1, 1);

        tabWidget->addTab(ftpProperties, QString());

        gridLayout_2->addWidget(tabWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1168, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);
        refreshFtpTableButton->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox_12->setTitle(QString());
        saveConfigButton->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\262\320\276\321\200\320\270\321\202\320\270 \320\272\320\276\320\275\321\204\321\226\320\263 \321\204\320\260\320\271\320\273", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(generalProperties), QCoreApplication::translate("MainWindow", "\320\236\321\201\320\275\320\276\320\262\320\275\321\226 \320\275\320\260\320\273\320\260\321\210\321\202\321\203\320\262\320\260\320\275\320\275\321\217 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\270", nullptr));
        groupBox_7->setTitle(QString());
        findUserLabel->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\321\210\321\203\320\272 \320\272\320\276\321\200\320\270\321\201\321\202\321\203\320\262\320\260\321\207\320\260", nullptr));
        deleteUserButton->setText(QCoreApplication::translate("MainWindow", "\320\222\320\270\320\264\320\260\320\273\320\270\321\202\320\270 ", nullptr));
        addUserButton->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\264\320\260\321\202\320\270", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(userProperties), QCoreApplication::translate("MainWindow", "\320\235\320\260\320\273\320\260\321\210\321\202\321\203\320\262\320\260\320\275\320\275\321\217 \320\272\320\276\321\200\320\270\321\201\321\202\321\203\320\262\320\260\321\207\321\226\320\262", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "\320\235\320\260\321\201\321\202\321\200\320\276\321\216\320\262\320\260\320\275\320\275\321\217 \320\277\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\226\320\262 \320\262\321\226\320\264\320\264\320\260\320\273\320\265\320\275\320\270\321\205 \321\201\320\265\321\200\320\262\320\265\321\200\321\226\320\262 \321\202\320\260 \320\273\320\276\320\272\320\260\320\273\321\214\320\275\320\270\321\205 \321\200\320\265\321\201\321\203\321\200\321\201\321\226\320\262 ", nullptr));
        collectionButton->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\270\320\274\321\203\321\201\320\276\320\262\320\270\320\271 \320\267\320\261\321\226\321\200", nullptr));
        filledParamsCheck->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\277\320\276\320\262\320\275\320\265\320\275\321\226 \320\277\320\260\321\200\320\260\320\274\320\265\321\202\321\200\320\270", nullptr));
        refreshFtpTableButton->setText(QCoreApplication::translate("MainWindow", "\320\236\320\275\320\276\320\262\320\270\321\202\320\270", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(ftpProperties), QCoreApplication::translate("MainWindow", "\320\235\320\260\321\201\321\202\321\200\320\276\321\216\320\262\320\260\320\275\320\275\321\217 \321\201\320\265\321\200\320\262\321\226\321\201\321\203 \320\267\320\261\320\270\321\200\320\260\320\275\320\275\321\217 \320\264\320\260\320\275\320\270\321\205 \320\277\320\276 FTP", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
