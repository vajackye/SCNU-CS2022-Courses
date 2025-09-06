/****************************************************************************
** Meta object code from reading C++ file 'tasktwowindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../run/tasktwowindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tasktwowindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TaskTwoWindow_t {
    QByteArrayData data[23];
    char stringdata0[249];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TaskTwoWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TaskTwoWindow_t qt_meta_stringdata_TaskTwoWindow = {
    {
QT_MOC_LITERAL(0, 0, 13), // "TaskTwoWindow"
QT_MOC_LITERAL(1, 14, 10), // "backToMain"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 9), // "inputFile"
QT_MOC_LITERAL(4, 36, 12), // "analysisGram"
QT_MOC_LITERAL(5, 49, 14), // "showExternGram"
QT_MOC_LITERAL(6, 64, 9), // "showFirst"
QT_MOC_LITERAL(7, 74, 10), // "showFollow"
QT_MOC_LITERAL(8, 85, 10), // "showLR0Dfa"
QT_MOC_LITERAL(9, 96, 9), // "judgeSLR1"
QT_MOC_LITERAL(10, 106, 10), // "showLR1Dfa"
QT_MOC_LITERAL(11, 117, 10), // "showLR1Tab"
QT_MOC_LITERAL(12, 128, 8), // "inputSrc"
QT_MOC_LITERAL(13, 137, 8), // "showProc"
QT_MOC_LITERAL(14, 146, 9), // "getAction"
QT_MOC_LITERAL(15, 156, 8), // "showTree"
QT_MOC_LITERAL(16, 165, 11), // "addUsageTip"
QT_MOC_LITERAL(17, 177, 11), // "getNodeText"
QT_MOC_LITERAL(18, 189, 15), // "SyntaxTreeNode*"
QT_MOC_LITERAL(19, 205, 4), // "node"
QT_MOC_LITERAL(20, 210, 10), // "addSubtree"
QT_MOC_LITERAL(21, 221, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(22, 238, 10) // "parentItem"

    },
    "TaskTwoWindow\0backToMain\0\0inputFile\0"
    "analysisGram\0showExternGram\0showFirst\0"
    "showFollow\0showLR0Dfa\0judgeSLR1\0"
    "showLR1Dfa\0showLR1Tab\0inputSrc\0showProc\0"
    "getAction\0showTree\0addUsageTip\0"
    "getNodeText\0SyntaxTreeNode*\0node\0"
    "addSubtree\0QTreeWidgetItem*\0parentItem"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TaskTwoWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   99,    2, 0x08 /* Private */,
       3,    0,  100,    2, 0x08 /* Private */,
       4,    0,  101,    2, 0x08 /* Private */,
       5,    0,  102,    2, 0x08 /* Private */,
       6,    0,  103,    2, 0x08 /* Private */,
       7,    0,  104,    2, 0x08 /* Private */,
       8,    0,  105,    2, 0x08 /* Private */,
       9,    0,  106,    2, 0x08 /* Private */,
      10,    0,  107,    2, 0x08 /* Private */,
      11,    0,  108,    2, 0x08 /* Private */,
      12,    0,  109,    2, 0x08 /* Private */,
      13,    0,  110,    2, 0x08 /* Private */,
      14,    0,  111,    2, 0x08 /* Private */,
      15,    0,  112,    2, 0x08 /* Private */,
      16,    0,  113,    2, 0x08 /* Private */,
      17,    1,  114,    2, 0x08 /* Private */,
      20,    2,  117,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::QString, 0x80000000 | 18,   19,
    QMetaType::Void, 0x80000000 | 21, 0x80000000 | 18,   22,   19,

       0        // eod
};

void TaskTwoWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TaskTwoWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->backToMain(); break;
        case 1: _t->inputFile(); break;
        case 2: _t->analysisGram(); break;
        case 3: _t->showExternGram(); break;
        case 4: _t->showFirst(); break;
        case 5: _t->showFollow(); break;
        case 6: _t->showLR0Dfa(); break;
        case 7: _t->judgeSLR1(); break;
        case 8: _t->showLR1Dfa(); break;
        case 9: _t->showLR1Tab(); break;
        case 10: _t->inputSrc(); break;
        case 11: _t->showProc(); break;
        case 12: _t->getAction(); break;
        case 13: _t->showTree(); break;
        case 14: _t->addUsageTip(); break;
        case 15: { QString _r = _t->getNodeText((*reinterpret_cast< SyntaxTreeNode*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 16: _t->addSubtree((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< SyntaxTreeNode*(*)>(_a[2]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject TaskTwoWindow::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_TaskTwoWindow.data,
    qt_meta_data_TaskTwoWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TaskTwoWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TaskTwoWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TaskTwoWindow.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int TaskTwoWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
