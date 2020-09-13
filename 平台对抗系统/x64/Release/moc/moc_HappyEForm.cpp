/****************************************************************************
** Meta object code from reading C++ file 'HappyEForm.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../HappyEForm.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'HappyEForm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_HappyEForm_t {
    QByteArrayData data[11];
    char stringdata0[93];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HappyEForm_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HappyEForm_t qt_meta_stringdata_HappyEForm = {
    {
QT_MOC_LITERAL(0, 0, 10), // "HappyEForm"
QT_MOC_LITERAL(1, 11, 9), // "doProcess"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 2), // "i1"
QT_MOC_LITERAL(4, 25, 2), // "j1"
QT_MOC_LITERAL(5, 28, 9), // "doRelease"
QT_MOC_LITERAL(6, 38, 2), // "i2"
QT_MOC_LITERAL(7, 41, 2), // "j2"
QT_MOC_LITERAL(8, 44, 7), // "REceive"
QT_MOC_LITERAL(9, 52, 20), // "on_btn_start_clicked"
QT_MOC_LITERAL(10, 73, 19) // "on_btn_auto_clicked"

    },
    "HappyEForm\0doProcess\0\0i1\0j1\0doRelease\0"
    "i2\0j2\0REceive\0on_btn_start_clicked\0"
    "on_btn_auto_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HappyEForm[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   39,    2, 0x08 /* Private */,
       5,    2,   44,    2, 0x08 /* Private */,
       8,    1,   49,    2, 0x08 /* Private */,
       9,    0,   52,    2, 0x08 /* Private */,
      10,    0,   53,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    6,    7,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void HappyEForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<HappyEForm *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->doProcess((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->doRelease((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->REceive((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->on_btn_start_clicked(); break;
        case 4: _t->on_btn_auto_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject HappyEForm::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_HappyEForm.data,
    qt_meta_data_HappyEForm,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *HappyEForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HappyEForm::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_HappyEForm.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int HappyEForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
