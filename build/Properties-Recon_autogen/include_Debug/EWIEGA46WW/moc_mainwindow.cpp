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
    "factoryID",
    "UpdateIpParams",
    "unit_id",
    "ipLogin",
    "ipPassword",
    "struct_id",
    "remotePath",
    "localPath",
    "previousUnit",
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
      33,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  212,    2, 0x08,    1 /* Private */,
       3,    4,  213,    2, 0x08,    2 /* Private */,
       9,    0,  222,    2, 0x08,    7 /* Private */,
      10,    0,  223,    2, 0x08,    8 /* Private */,
      11,    1,  224,    2, 0x08,    9 /* Private */,
      13,    0,  227,    2, 0x08,   11 /* Private */,
      14,    0,  228,    2, 0x08,   12 /* Private */,
      15,    0,  229,    2, 0x08,   13 /* Private */,
      16,    0,  230,    2, 0x08,   14 /* Private */,
      17,    1,  231,    2, 0x08,   15 /* Private */,
      19,    0,  234,    2, 0x08,   17 /* Private */,
      20,    0,  235,    2, 0x08,   18 /* Private */,
      21,    7,  236,    2, 0x08,   19 /* Private */,
      35,    1,  251,    2, 0x08,   27 /* Private */,
      37,    1,  254,    2, 0x08,   29 /* Private */,
      38,    1,  257,    2, 0x08,   31 /* Private */,
      39,    2,  260,    2, 0x08,   33 /* Private */,
      41,    1,  265,    2, 0x08,   36 /* Private */,
      43,    1,  268,    2, 0x08,   38 /* Private */,
      46,    1,  271,    2, 0x08,   40 /* Private */,
      48,    2,  274,    2, 0x08,   42 /* Private */,
      52,    4,  279,    2, 0x08,   45 /* Private */,
      57,    3,  288,    2, 0x08,   50 /* Private */,
      58,    3,  295,    2, 0x08,   54 /* Private */,
      59,    3,  302,    2, 0x08,   58 /* Private */,
      60,    1,  309,    2, 0x08,   62 /* Private */,
      61,    4,  312,    2, 0x08,   64 /* Private */,
      66,    4,  321,    2, 0x08,   69 /* Private */,
      67,    2,  330,    2, 0x08,   74 /* Private */,
      69,    8,  335,    2, 0x08,   77 /* Private */,
      77,    3,  352,    2, 0x08,   86 /* Private */,
      80,    0,  359,    2, 0x08,   90 /* Private */,
      81,    1,  360,    2, 0x08,   91 /* Private */,

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
    QMetaType::Bool, QMetaType::QString,   36,
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,   18,   40,
    QMetaType::Void, QMetaType::QString,   42,
    QMetaType::Void, 0x80000000 | 44,   45,
    QMetaType::Void, QMetaType::QStringList,   47,
    0x80000000 | 22, QMetaType::QString, 0x80000000 | 50,   49,   51,
    QMetaType::Void, 0x80000000 | 53, QMetaType::QString, QMetaType::QString, 0x80000000 | 55,   54,   49,   51,   56,
    QMetaType::Void, 0x80000000 | 53, QMetaType::QString, QMetaType::QString,   54,   49,   51,
    QMetaType::Void, 0x80000000 | 53, QMetaType::QString, QMetaType::QString,   54,   49,   51,
    QMetaType::Void, 0x80000000 | 53, QMetaType::QString, 0x80000000 | 50,   54,   49,   51,
    QMetaType::Bool, QMetaType::QString,   49,
    QMetaType::Bool, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,   62,   63,   64,   65,
    QMetaType::Bool, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,   62,   63,   64,   65,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,   68,   40,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,   70,   62,   71,   72,   73,   74,   75,   76,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   73,   78,   79,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   82,

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
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<QPushButton *, std::false_type>,
        // method 'setupOnedriveSettings'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QVBoxLayout *, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'setupRootDirectorySettings'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QVBoxLayout *, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'setupDefaultSettings'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QVBoxLayout *, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
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
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'UpdateIpParams'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
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
        case 13: { bool _r = _t->CheckObjectsSelection((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 14: _t->FillAdminObjects((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 15: _t->FillUserObjects((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 16: _t->UpdateUserStatus((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2]))); break;
        case 17: _t->FilterUsers((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 18: _t->OnFactorySelected((*reinterpret_cast< std::add_pointer_t<QTableWidgetItem*>>(_a[1]))); break;
        case 19: _t->OpenFactoryDialog((*reinterpret_cast< std::add_pointer_t<QStringList>>(_a[1]))); break;
        case 20: { QDialog* _r = _t->createDialog((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString&>>(_a[2])));
            if (_a[0]) *reinterpret_cast< QDialog**>(_a[0]) = std::move(_r); }  break;
        case 21: _t->setupMailSettings((*reinterpret_cast< std::add_pointer_t<QVBoxLayout*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QPushButton*>>(_a[4]))); break;
        case 22: _t->setupOnedriveSettings((*reinterpret_cast< std::add_pointer_t<QVBoxLayout*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3]))); break;
        case 23: _t->setupRootDirectorySettings((*reinterpret_cast< std::add_pointer_t<QVBoxLayout*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3]))); break;
        case 24: _t->setupDefaultSettings((*reinterpret_cast< std::add_pointer_t<QVBoxLayout*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString&>>(_a[3]))); break;
        case 25: { bool _r = _t->saveSettings((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 26: { bool _r = _t->CheckFtpConnection((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[4])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 27: { bool _r = _t->CheckFtpFolderExists((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[4])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 28: _t->UpdateFactoryStatus((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2]))); break;
        case 29: _t->UpdateIpParams((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[6])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[7])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[8]))); break;
        case 30: _t->InsertDirValue((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3]))); break;
        case 31: _t->FillMissingData(); break;
        case 32: _t->updateGroupSetting((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 21:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 3:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QPushButton* >(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QVBoxLayout* >(); break;
            }
            break;
        case 22:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QVBoxLayout* >(); break;
            }
            break;
        case 23:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
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
        if (_id < 33)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 33;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 33)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 33;
    }
    return _id;
}
QT_WARNING_POP
