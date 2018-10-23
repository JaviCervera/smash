/****************************************************************************
** Meta object code from reading C++ file 'event.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "event.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'event.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_EventDispatcher_t {
    QByteArrayData data[24];
    char stringdata0[298];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EventDispatcher_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EventDispatcher_t qt_meta_stringdata_EventDispatcher = {
    {
QT_MOC_LITERAL(0, 0, 15), // "EventDispatcher"
QT_MOC_LITERAL(1, 16, 4), // "Init"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 13), // "ButtonPressed"
QT_MOC_LITERAL(4, 36, 7), // "checked"
QT_MOC_LITERAL(5, 44, 17), // "EditorTextChanged"
QT_MOC_LITERAL(6, 62, 17), // "EditorCursorMoved"
QT_MOC_LITERAL(7, 80, 19), // "LineEditTextChanged"
QT_MOC_LITERAL(8, 100, 4), // "text"
QT_MOC_LITERAL(9, 105, 10), // "MenuAction"
QT_MOC_LITERAL(10, 116, 18), // "TabBarChangedIndex"
QT_MOC_LITERAL(11, 135, 5), // "index"
QT_MOC_LITERAL(12, 141, 11), // "CloseWindow"
QT_MOC_LITERAL(13, 153, 7), // "Window*"
QT_MOC_LITERAL(14, 161, 3), // "win"
QT_MOC_LITERAL(15, 165, 10), // "SizeWindow"
QT_MOC_LITERAL(16, 176, 12), // "ProgramError"
QT_MOC_LITERAL(17, 189, 22), // "QProcess::ProcessError"
QT_MOC_LITERAL(18, 212, 5), // "error"
QT_MOC_LITERAL(19, 218, 15), // "ProgramFinished"
QT_MOC_LITERAL(20, 234, 8), // "exitCode"
QT_MOC_LITERAL(21, 243, 20), // "QProcess::ExitStatus"
QT_MOC_LITERAL(22, 264, 10), // "exitStatus"
QT_MOC_LITERAL(23, 275, 22) // "ProgramOutputAvailable"

    },
    "EventDispatcher\0Init\0\0ButtonPressed\0"
    "checked\0EditorTextChanged\0EditorCursorMoved\0"
    "LineEditTextChanged\0text\0MenuAction\0"
    "TabBarChangedIndex\0index\0CloseWindow\0"
    "Window*\0win\0SizeWindow\0ProgramError\0"
    "QProcess::ProcessError\0error\0"
    "ProgramFinished\0exitCode\0QProcess::ExitStatus\0"
    "exitStatus\0ProgramOutputAvailable"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EventDispatcher[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x0a /* Public */,
       3,    1,   75,    2, 0x0a /* Public */,
       5,    0,   78,    2, 0x0a /* Public */,
       6,    0,   79,    2, 0x0a /* Public */,
       7,    1,   80,    2, 0x0a /* Public */,
       9,    0,   83,    2, 0x0a /* Public */,
      10,    1,   84,    2, 0x0a /* Public */,
      12,    1,   87,    2, 0x0a /* Public */,
      15,    1,   90,    2, 0x0a /* Public */,
      16,    1,   93,    2, 0x0a /* Public */,
      19,    2,   96,    2, 0x0a /* Public */,
      23,    0,  101,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 21,   20,   22,
    QMetaType::Void,

       0        // eod
};

void EventDispatcher::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        EventDispatcher *_t = static_cast<EventDispatcher *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Init(); break;
        case 1: _t->ButtonPressed((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->EditorTextChanged(); break;
        case 3: _t->EditorCursorMoved(); break;
        case 4: _t->LineEditTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->MenuAction(); break;
        case 6: _t->TabBarChangedIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->CloseWindow((*reinterpret_cast< Window*(*)>(_a[1]))); break;
        case 8: _t->SizeWindow((*reinterpret_cast< Window*(*)>(_a[1]))); break;
        case 9: _t->ProgramError((*reinterpret_cast< QProcess::ProcessError(*)>(_a[1]))); break;
        case 10: _t->ProgramFinished((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QProcess::ExitStatus(*)>(_a[2]))); break;
        case 11: _t->ProgramOutputAvailable(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject EventDispatcher::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_EventDispatcher.data,
      qt_meta_data_EventDispatcher,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *EventDispatcher::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EventDispatcher::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_EventDispatcher.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int EventDispatcher::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
