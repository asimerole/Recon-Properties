/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../mainwindow.h"
#include <QtGui/qtextcursor.h>
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN10MainWindowE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN10MainWindowE = QtMocHelpers::stringData(
    "MainWindow",
    "CreateConfigFile",
    "",
    "encryptDataToFile",
    "data",
    "filePath",
    "const uchar*",
    "key",
    "iv",
    "AddUserToDB",
    "UpdateUser",
    "updateSelectedObjects",
    "userRow",
    "DeleteUser",
    "SelectObjects",
    "LoadUsers",
    "LoadServiceTree",
    "HandleChangePassword",
    "userID",
    "LoadSettings",
    "OpenEditSettingsDialog",
    "CreateUserDialog",
    "QDialog*",
    "QLineEdit*&",
    "userLoginEdit",
    "userWorkPosition",
    "QComboBox*&",
    "userTypeComboBox",
    "QCheckBox*&",
    "userMailingDataCheck",
    "QPushButton*&",
    "objectsButton",
    "actionButton",
    "QLabel*&",
    "errorLabel",
    "toggleRowVisibility",
    "parentRow",
    "parentColumn",
    "collapse",
    "AddTextWithButton",
    "row",
    "column",
    "text",
    "CheckObjectsSelection",
    "userType",
    "FillAdminObjects",
    "FillUserObjects",
    "UpdateUserStatus",
    "isActive",
    "FilterUsers",
    "searchText",
    "OnFactorySelected",
    "QTableWidgetItem*",
    "item",
    "OpenFactoryDialog",
    "rowData",
    "createDialog",
    "name",
    "QString&",
    "value",
    "setupMailSettings",
    "QVBoxLayout*",
    "layout",
    "QPushButton*",
    "saveButton",
    "setupOnedriveSettings",
    "setupRootDirectorySettings",
    "setupDefaultSettings",
    "saveSettings",
    "CheckFtpConnection",
    "ipAddress",
    "remoteFolder",
    "username",
    "password",
    "CheckFtpFolderExists",
    "UpdateFactoryStatus",
    "UpdateFourDigitsStatus",
    "remotePath",
    "isTrue",
    "UpdateIpParams",
    "int&",
    "unit_id",
    "prevIP",
    "ipLogin",
    "ipPassword",
    "struct_id",
    "localPath",
    "previousUnit",
    "isMultiple",
    "CheckEmptyFieldsFactoryDialog",
    "QLineEdit*",
    "ipAddressEdit",
    "ipLoginEdit",
    "ipPasswordEdit",
    "remotePathEdit",
    "getIpRecords",
    "QList<QVariantMap>",
    "ip",
    "handleMultipleIpUpdate",
    "currentMultiple",
    "numUnits",
    "ipFromTable",
    "QVariant",
    "unitId",
    "ipAddr",
    "login",
    "status",
    "loadIpCredentials",
    "updateSubstationLabel",
    "QLabel*",
    "substationLabel",
    "QCheckBox*",
    "ipMultipleCheckBox",
    "updateIpAssignment",
    "isMultipleIpCheckBox",
    "unmarkAsMultipleAndCleanOthers",
    "currentUnitId",
    "DeleteAddress",
    "InsertDirValue",
    "remote_path",
    "local_path",
    "FillMissingData",
    "updateGroupSetting",
    "checked"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN10MainWindowE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      43,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  272,    2, 0x08,    1 /* Private */,
       3,    4,  273,    2, 0x08,    2 /* Private */,
       9,    0,  282,    2, 0x08,    7 /* Private */,
      10,    0,  283,    2, 0x08,    8 /* Private */,
      11,    1,  284,    2, 0x08,    9 /* Private */,
      13,    0,  287,    2, 0x08,   11 /* Private */,
      14,    0,  288,    2, 0x08,   12 /* Private */,
      15,    0,  289,    2, 0x08,   13 /* Private */,
      16,    0,  290,    2, 0x08,   14 /* Private */,
      17,    1,  291,    2, 0x08,   15 /* Private */,
      19,    0,  294,    2, 0x08,   17 /* Private */,
      20,    0,  295,    2, 0x08,   18 /* Private */,
      21,    7,  296,    2, 0x08,   19 /* Private */,
      35,    3,  311,    2, 0x08,   27 /* Private */,
      39,    3,  318,    2, 0x08,   31 /* Private */,
      43,    1,  325,    2, 0x08,   35 /* Private */,
      45,    1,  328,    2, 0x08,   37 /* Private */,
      46,    1,  331,    2, 0x08,   39 /* Private */,
      47,    2,  334,    2, 0x08,   41 /* Private */,
      49,    1,  339,    2, 0x08,   44 /* Private */,
      51,    1,  342,    2, 0x08,   46 /* Private */,
      54,    1,  345,    2, 0x08,   48 /* Private */,
      56,    2,  348,    2, 0x08,   50 /* Private */,
      60,    3,  353,    2, 0x08,   53 /* Private */,
      65,    2,  360,    2, 0x08,   57 /* Private */,
      66,    2,  365,    2, 0x08,   60 /* Private */,
      67,    2,  370,    2, 0x08,   63 /* Private */,
      68,    1,  375,    2, 0x08,   66 /* Private */,
      69,    4,  378,    2, 0x08,   68 /* Private */,
      74,    4,  387,    2, 0x08,   73 /* Private */,
      75,    2,  396,    2, 0x08,   78 /* Private */,
      76,    2,  401,    2, 0x08,   81 /* Private */,
      79,   10,  406,    2, 0x08,   84 /* Private */,
      89,    4,  427,    2, 0x08,   95 /* Private */,
      95,    1,  436,    2, 0x08,  100 /* Private */,
      98,   10,  439,    2, 0x08,  102 /* Private */,
     107,    6,  460,    2, 0x08,  113 /* Private */,
     113,    6,  473,    2, 0x08,  120 /* Private */,
     115,    2,  486,    2, 0x08,  127 /* Private */,
     117,    2,  491,    2, 0x08,  130 /* Private */,
     118,    3,  496,    2, 0x08,  133 /* Private */,
     121,    0,  503,    2, 0x08,  137 /* Private */,
     122,    1,  504,    2, 0x08,  138 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Bool, QMetaType::QByteArray, QMetaType::QString, 0x80000000 | 6, 0x80000000 | 6,    4,    5,    7,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Void,
    QMetaType::Void,
    0x80000000 | 22, 0x80000000 | 23, 0x80000000 | 23, 0x80000000 | 26, 0x80000000 | 28, 0x80000000 | 30, 0x80000000 | 30, 0x80000000 | 33,   24,   25,   27,   29,   31,   32,   34,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Bool,   36,   37,   38,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::QString,   40,   41,   42,
    QMetaType::Bool, QMetaType::QString,   44,
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,   18,   48,
    QMetaType::Void, QMetaType::QString,   50,
    QMetaType::Void, 0x80000000 | 52,   53,
    QMetaType::Void, QMetaType::QStringList,   55,
    0x80000000 | 22, QMetaType::QString, 0x80000000 | 58,   57,   59,
    QMetaType::Void, 0x80000000 | 61, QMetaType::QString, 0x80000000 | 63,   62,   59,   64,
    QMetaType::Void, 0x80000000 | 61, QMetaType::QString,   62,   59,
    QMetaType::Void, 0x80000000 | 61, QMetaType::QString,   62,   59,
    QMetaType::Void, 0x80000000 | 61, 0x80000000 | 58,   62,   59,
    QMetaType::Bool, QMetaType::QString,   57,
    QMetaType::Bool, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,   70,   71,   72,   73,
    QMetaType::Bool, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,   70,   71,   72,   73,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,   70,   48,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,   77,   78,
    QMetaType::Void, 0x80000000 | 80, 0x80000000 | 58, 0x80000000 | 58, 0x80000000 | 58, 0x80000000 | 58, 0x80000000 | 58, 0x80000000 | 58, 0x80000000 | 58, 0x80000000 | 58, QMetaType::Bool,   81,   70,   82,   83,   84,   85,   77,   86,   87,   88,
    QMetaType::Bool, 0x80000000 | 90, 0x80000000 | 90, 0x80000000 | 90, 0x80000000 | 90,   91,   92,   93,   94,
    0x80000000 | 96, QMetaType::QString,   97,
    QMetaType::Bool, QMetaType::Bool, QMetaType::Bool, QMetaType::Int, QMetaType::QString, 0x80000000 | 102, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::Int, 0x80000000 | 102,   88,   99,  100,  101,  103,  104,  105,   73,  106,   87,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool, 0x80000000 | 109, 0x80000000 | 90, 0x80000000 | 90, 0x80000000 | 111,   97,  108,  110,   92,   93,  112,
    QMetaType::Void, QMetaType::QStringList, 0x80000000 | 90, 0x80000000 | 90, 0x80000000 | 90, 0x80000000 | 90, 0x80000000 | 111,   55,   91,   92,   93,   94,  114,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   97,  116,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 90,   81,   91,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   85,  119,  120,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,  123,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_ZN10MainWindowE.offsetsAndSizes,
    qt_meta_data_ZN10MainWindowE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN10MainWindowE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'CreateConfigFile'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'encryptDataToFile'
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QByteArray &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const unsigned char *, std::false_type>,
        QtPrivate::TypeAndForceComplete<const unsigned char *, std::false_type>,
        // method 'AddUserToDB'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'UpdateUser'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateSelectedObjects'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'DeleteUser'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'SelectObjects'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'LoadUsers'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'LoadServiceTree'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'HandleChangePassword'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'LoadSettings'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'OpenEditSettingsDialog'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'CreateUserDialog'
        QtPrivate::TypeAndForceComplete<QDialog *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QLineEdit * &, std::false_type>,
        QtPrivate::TypeAndForceComplete<QLineEdit * &, std::false_type>,
        QtPrivate::TypeAndForceComplete<QComboBox * &, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCheckBox * &, std::false_type>,
        QtPrivate::TypeAndForceComplete<QPushButton * &, std::false_type>,
        QtPrivate::TypeAndForceComplete<QPushButton * &, std::false_type>,
        QtPrivate::TypeAndForceComplete<QLabel * &, std::false_type>,
        // method 'toggleRowVisibility'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'AddTextWithButton'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'CheckObjectsSelection'
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'FillAdminObjects'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'FillUserObjects'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'UpdateUserStatus'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'FilterUsers'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'OnFactorySelected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QTableWidgetItem *, std::false_type>,
        // method 'OpenFactoryDialog'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QStringList &, std::false_type>,
        // method 'createDialog'
        QtPrivate::TypeAndForceComplete<QDialog *, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString &, std::false_type>,
        // method 'setupMailSettings'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QVBoxLayout *, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<QPushButton *, std::false_type>,
        // method 'setupOnedriveSettings'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QVBoxLayout *, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'setupRootDirectorySettings'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QVBoxLayout *, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'setupDefaultSettings'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QVBoxLayout *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString &, std::false_type>,
        // method 'saveSettings'
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'CheckFtpConnection'
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'CheckFtpFolderExists'
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'UpdateFactoryStatus'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'UpdateFourDigitsStatus'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'UpdateIpParams'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int &, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'CheckEmptyFieldsFactoryDialog'
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<QLineEdit *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QLineEdit *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QLineEdit *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QLineEdit *, std::false_type>,
        // method 'getIpRecords'
        QtPrivate::TypeAndForceComplete<QList<QVariantMap>, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'handleMultipleIpUpdate'
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QVariant &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QVariant &, std::false_type>,
        // method 'loadIpCredentials'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<QLabel *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QLineEdit *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QLineEdit *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCheckBox *, std::false_type>,
        // method 'updateIpAssignment'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QStringList &, std::false_type>,
        QtPrivate::TypeAndForceComplete<QLineEdit *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QLineEdit *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QLineEdit *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QLineEdit *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCheckBox *, std::false_type>,
        // method 'unmarkAsMultipleAndCleanOthers'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'DeleteAddress'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QLineEdit *, std::false_type>,
        // method 'InsertDirValue'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'FillMissingData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateGroupSetting'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<MainWindow *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->CreateConfigFile(); break;
        case 1: { bool _r = _t->encryptDataToFile((*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<const uchar*>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<const uchar*>>(_a[4])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 2: _t->AddUserToDB(); break;
        case 3: _t->UpdateUser(); break;
        case 4: _t->updateSelectedObjects((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 5: _t->DeleteUser(); break;
        case 6: _t->SelectObjects(); break;
        case 7: _t->LoadUsers(); break;
        case 8: _t->LoadServiceTree(); break;
        case 9: _t->HandleChangePassword((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 10: _t->LoadSettings(); break;
        case 11: _t->OpenEditSettingsDialog(); break;
        case 12: { QDialog* _r = _t->CreateUserDialog((*reinterpret_cast< std::add_pointer_t<QLineEdit*&>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QLineEdit*&>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QComboBox*&>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QCheckBox*&>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<QPushButton*&>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<QPushButton*&>>(_a[6])),(*reinterpret_cast< std::add_pointer_t<QLabel*&>>(_a[7])));
            if (_a[0]) *reinterpret_cast< QDialog**>(_a[0]) = std::move(_r); }  break;
        case 13: _t->toggleRowVisibility((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[3]))); break;
        case 14: _t->AddTextWithButton((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3]))); break;
        case 15: { bool _r = _t->CheckObjectsSelection((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 16: _t->FillAdminObjects((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 17: _t->FillUserObjects((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 18: _t->UpdateUserStatus((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2]))); break;
        case 19: _t->FilterUsers((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 20: _t->OnFactorySelected((*reinterpret_cast< std::add_pointer_t<QTableWidgetItem*>>(_a[1]))); break;
        case 21: _t->OpenFactoryDialog((*reinterpret_cast< std::add_pointer_t<QStringList>>(_a[1]))); break;
        case 22: { QDialog* _r = _t->createDialog((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString&>>(_a[2])));
            if (_a[0]) *reinterpret_cast< QDialog**>(_a[0]) = std::move(_r); }  break;
        case 23: _t->setupMailSettings((*reinterpret_cast< std::add_pointer_t<QVBoxLayout*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QPushButton*>>(_a[3]))); break;
        case 24: _t->setupOnedriveSettings((*reinterpret_cast< std::add_pointer_t<QVBoxLayout*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 25: _t->setupRootDirectorySettings((*reinterpret_cast< std::add_pointer_t<QVBoxLayout*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 26: _t->setupDefaultSettings((*reinterpret_cast< std::add_pointer_t<QVBoxLayout*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString&>>(_a[2]))); break;
        case 27: { bool _r = _t->saveSettings((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 28: { bool _r = _t->CheckFtpConnection((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[4])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 29: { bool _r = _t->CheckFtpFolderExists((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[4])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 30: _t->UpdateFactoryStatus((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2]))); break;
        case 31: _t->UpdateFourDigitsStatus((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2]))); break;
        case 32: _t->UpdateIpParams((*reinterpret_cast< std::add_pointer_t<int&>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString&>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString&>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QString&>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<QString&>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<QString&>>(_a[6])),(*reinterpret_cast< std::add_pointer_t<QString&>>(_a[7])),(*reinterpret_cast< std::add_pointer_t<QString&>>(_a[8])),(*reinterpret_cast< std::add_pointer_t<QString&>>(_a[9])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[10]))); break;
        case 33: { bool _r = _t->CheckEmptyFieldsFactoryDialog((*reinterpret_cast< std::add_pointer_t<QLineEdit*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QLineEdit*>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QLineEdit*>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QLineEdit*>>(_a[4])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 34: { QList<QVariantMap> _r = _t->getIpRecords((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QList<QVariantMap>*>(_a[0]) = std::move(_r); }  break;
        case 35: { bool _r = _t->handleMultipleIpUpdate((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<QVariant>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[6])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[7])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[8])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[9])),(*reinterpret_cast< std::add_pointer_t<QVariant>>(_a[10])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 36: _t->loadIpCredentials((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QLabel*>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QLineEdit*>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<QLineEdit*>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<QCheckBox*>>(_a[6]))); break;
        case 37: _t->updateIpAssignment((*reinterpret_cast< std::add_pointer_t<QStringList>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QLineEdit*>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QLineEdit*>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QLineEdit*>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<QLineEdit*>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<QCheckBox*>>(_a[6]))); break;
        case 38: _t->unmarkAsMultipleAndCleanOthers((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 39: _t->DeleteAddress((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QLineEdit*>>(_a[2]))); break;
        case 40: _t->InsertDirValue((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3]))); break;
        case 41: _t->FillMissingData(); break;
        case 42: _t->updateGroupSetting((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 23:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 2:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QPushButton* >(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QVBoxLayout* >(); break;
            }
            break;
        case 24:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QVBoxLayout* >(); break;
            }
            break;
        case 25:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QVBoxLayout* >(); break;
            }
            break;
        case 26:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QVBoxLayout* >(); break;
            }
            break;
        case 33:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 3:
            case 2:
            case 1:
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QLineEdit* >(); break;
            }
            break;
        case 36:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 5:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCheckBox* >(); break;
            case 2:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QLabel* >(); break;
            case 4:
            case 3:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QLineEdit* >(); break;
            }
            break;
        case 37:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 5:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCheckBox* >(); break;
            case 4:
            case 3:
            case 2:
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QLineEdit* >(); break;
            }
            break;
        case 39:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QLineEdit* >(); break;
            }
            break;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN10MainWindowE.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 43)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 43;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 43)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 43;
    }
    return _id;
}
QT_WARNING_POP
