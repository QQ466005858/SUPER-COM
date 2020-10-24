/****************************************************************************
** Meta object code from reading C++ file 'DeviceModel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../DeviceLibrary/DeviceModel/DeviceModel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DeviceModel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DeviceModel_t {
    QByteArrayData data[10];
    char stringdata0[128];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DeviceModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DeviceModel_t qt_meta_stringdata_DeviceModel = {
    {
QT_MOC_LITERAL(0, 0, 11), // "DeviceModel"
QT_MOC_LITERAL(1, 12, 22), // "report_reg_data_signal"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 13), // "QList<reg_s*>"
QT_MOC_LITERAL(4, 50, 6), // "Dev_s*"
QT_MOC_LITERAL(5, 57, 10), // "testSignal"
QT_MOC_LITERAL(6, 68, 23), // "report_reg_write_signal"
QT_MOC_LITERAL(7, 92, 21), // "receive_reg_data_slot"
QT_MOC_LITERAL(8, 114, 8), // "testSlot"
QT_MOC_LITERAL(9, 123, 4) // "slot"

    },
    "DeviceModel\0report_reg_data_signal\0\0"
    "QList<reg_s*>\0Dev_s*\0testSignal\0"
    "report_reg_write_signal\0receive_reg_data_slot\0"
    "testSlot\0slot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DeviceModel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   39,    2, 0x06 /* Public */,
       5,    1,   44,    2, 0x06 /* Public */,
       6,    2,   47,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    2,   52,    2, 0x0a /* Public */,
       8,    1,   57,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 4,    2,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 4,    2,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 4,    2,    2,
    QMetaType::Void, QMetaType::QString,    9,

       0        // eod
};

void DeviceModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DeviceModel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->report_reg_data_signal((*reinterpret_cast< QList<reg_s*>(*)>(_a[1])),(*reinterpret_cast< Dev_s*(*)>(_a[2]))); break;
        case 1: _t->testSignal((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->report_reg_write_signal((*reinterpret_cast< QList<reg_s*>(*)>(_a[1])),(*reinterpret_cast< Dev_s*(*)>(_a[2]))); break;
        case 3: _t->receive_reg_data_slot((*reinterpret_cast< QList<reg_s*>(*)>(_a[1])),(*reinterpret_cast< Dev_s*(*)>(_a[2]))); break;
        case 4: _t->testSlot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DeviceModel::*)(QList<reg_s*> , Dev_s * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DeviceModel::report_reg_data_signal)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DeviceModel::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DeviceModel::testSignal)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (DeviceModel::*)(QList<reg_s*> , Dev_s * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DeviceModel::report_reg_write_signal)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DeviceModel::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_DeviceModel.data,
    qt_meta_data_DeviceModel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DeviceModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DeviceModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DeviceModel.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int DeviceModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void DeviceModel::report_reg_data_signal(QList<reg_s*> _t1, Dev_s * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DeviceModel::testSignal(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DeviceModel::report_reg_write_signal(QList<reg_s*> _t1, Dev_s * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
