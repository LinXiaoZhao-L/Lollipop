/****************************************************************************
** Meta object code from reading C++ file 'PlayerForm.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../PlayerForm.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PlayerForm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PlayerForm_t {
    QByteArrayData data[18];
    char stringdata0[197];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PlayerForm_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PlayerForm_t qt_meta_stringdata_PlayerForm = {
    {
QT_MOC_LITERAL(0, 0, 10), // "PlayerForm"
QT_MOC_LITERAL(1, 11, 8), // "ShowMain"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 9), // "StartGame"
QT_MOC_LITERAL(4, 31, 2), // "Me"
QT_MOC_LITERAL(5, 34, 2), // "Ta"
QT_MOC_LITERAL(6, 37, 4), // "Gage"
QT_MOC_LITERAL(7, 42, 8), // "StartPVE"
QT_MOC_LITERAL(8, 51, 6), // "Player"
QT_MOC_LITERAL(9, 58, 14), // "on_PVP_clicked"
QT_MOC_LITERAL(10, 73, 15), // "on_Rank_clicked"
QT_MOC_LITERAL(11, 89, 17), // "on_PVE_GB_clicked"
QT_MOC_LITERAL(12, 107, 17), // "on_PVE_HE_clicked"
QT_MOC_LITERAL(13, 125, 15), // "on_back_clicked"
QT_MOC_LITERAL(14, 141, 18), // "on_Refresh_clicked"
QT_MOC_LITERAL(15, 160, 12), // "ReceiveAUser"
QT_MOC_LITERAL(16, 173, 4), // "User"
QT_MOC_LITERAL(17, 178, 18) // "doProcessReadyRead"

    },
    "PlayerForm\0ShowMain\0\0StartGame\0Me\0Ta\0"
    "Gage\0StartPVE\0Player\0on_PVP_clicked\0"
    "on_Rank_clicked\0on_PVE_GB_clicked\0"
    "on_PVE_HE_clicked\0on_back_clicked\0"
    "on_Refresh_clicked\0ReceiveAUser\0User\0"
    "doProcessReadyRead"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PlayerForm[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,
       3,    3,   72,    2, 0x06 /* Public */,
       7,    1,   79,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   82,    2, 0x08 /* Private */,
      10,    0,   83,    2, 0x08 /* Private */,
      11,    0,   84,    2, 0x08 /* Private */,
      12,    0,   85,    2, 0x08 /* Private */,
      13,    0,   86,    2, 0x08 /* Private */,
      14,    0,   87,    2, 0x08 /* Private */,
      15,    1,   88,    2, 0x08 /* Private */,
      17,    0,   91,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Int,    4,    5,    6,
    QMetaType::Void, QMetaType::QString,    8,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void,

       0        // eod
};

void PlayerForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PlayerForm *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ShowMain((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->StartGame((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 2: _t->StartPVE((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->on_PVP_clicked(); break;
        case 4: _t->on_Rank_clicked(); break;
        case 5: _t->on_PVE_GB_clicked(); break;
        case 6: _t->on_PVE_HE_clicked(); break;
        case 7: _t->on_back_clicked(); break;
        case 8: _t->on_Refresh_clicked(); break;
        case 9: _t->ReceiveAUser((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->doProcessReadyRead(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PlayerForm::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PlayerForm::ShowMain)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PlayerForm::*)(QString , QString , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PlayerForm::StartGame)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (PlayerForm::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PlayerForm::StartPVE)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PlayerForm::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_PlayerForm.data,
    qt_meta_data_PlayerForm,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PlayerForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PlayerForm::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PlayerForm.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int PlayerForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void PlayerForm::ShowMain(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PlayerForm::StartGame(QString _t1, QString _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PlayerForm::StartPVE(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
