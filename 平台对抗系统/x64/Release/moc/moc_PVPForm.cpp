/****************************************************************************
** Meta object code from reading C++ file 'PVPForm.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../PVPForm.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PVPForm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PVPForm_t {
    QByteArrayData data[18];
    char stringdata0[232];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PVPForm_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PVPForm_t qt_meta_stringdata_PVPForm = {
    {
QT_MOC_LITERAL(0, 0, 7), // "PVPForm"
QT_MOC_LITERAL(1, 8, 19), // "on_btn_Send_clicked"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 20), // "on_btn_Empty_clicked"
QT_MOC_LITERAL(4, 50, 20), // "on_btn_start_clicked"
QT_MOC_LITERAL(5, 71, 20), // "on_btn_peace_clicked"
QT_MOC_LITERAL(6, 92, 21), // "on_btn_regret_clicked"
QT_MOC_LITERAL(7, 114, 21), // "on_btn_giveup_clicked"
QT_MOC_LITERAL(8, 136, 18), // "doProcessReadyRead"
QT_MOC_LITERAL(9, 155, 9), // "doProcess"
QT_MOC_LITERAL(10, 165, 1), // "i"
QT_MOC_LITERAL(11, 167, 1), // "j"
QT_MOC_LITERAL(12, 169, 7), // "Receive"
QT_MOC_LITERAL(13, 177, 2), // "Me"
QT_MOC_LITERAL(14, 180, 2), // "Ta"
QT_MOC_LITERAL(15, 183, 4), // "Gage"
QT_MOC_LITERAL(16, 188, 14), // "doProcessError"
QT_MOC_LITERAL(17, 203, 28) // "QAbstractSocket::SocketError"

    },
    "PVPForm\0on_btn_Send_clicked\0\0"
    "on_btn_Empty_clicked\0on_btn_start_clicked\0"
    "on_btn_peace_clicked\0on_btn_regret_clicked\0"
    "on_btn_giveup_clicked\0doProcessReadyRead\0"
    "doProcess\0i\0j\0Receive\0Me\0Ta\0Gage\0"
    "doProcessError\0QAbstractSocket::SocketError"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PVPForm[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x08 /* Private */,
       3,    0,   65,    2, 0x08 /* Private */,
       4,    0,   66,    2, 0x08 /* Private */,
       5,    0,   67,    2, 0x08 /* Private */,
       6,    0,   68,    2, 0x08 /* Private */,
       7,    0,   69,    2, 0x08 /* Private */,
       8,    0,   70,    2, 0x08 /* Private */,
       9,    2,   71,    2, 0x08 /* Private */,
      12,    3,   76,    2, 0x08 /* Private */,
      16,    1,   83,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   10,   11,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Int,   13,   14,   15,
    QMetaType::Void, 0x80000000 | 17,    2,

       0        // eod
};

void PVPForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PVPForm *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_btn_Send_clicked(); break;
        case 1: _t->on_btn_Empty_clicked(); break;
        case 2: _t->on_btn_start_clicked(); break;
        case 3: _t->on_btn_peace_clicked(); break;
        case 4: _t->on_btn_regret_clicked(); break;
        case 5: _t->on_btn_giveup_clicked(); break;
        case 6: _t->doProcessReadyRead(); break;
        case 7: _t->doProcess((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->Receive((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 9: _t->doProcessError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PVPForm::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_PVPForm.data,
    qt_meta_data_PVPForm,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PVPForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PVPForm::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PVPForm.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int PVPForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
