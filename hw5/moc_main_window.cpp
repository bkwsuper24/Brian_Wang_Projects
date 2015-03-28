/****************************************************************************
** Meta object code from reading C++ file 'main_window.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "main_window.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'main_window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Main_Window[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      19,   13,   12,   12, 0x08,
      31,   12,   12,   12, 0x08,
      40,   12,   12,   12, 0x08,
      52,   12,   12,   12, 0x08,
      60,   12,   12,   12, 0x08,
      70,   12,   12,   12, 0x08,
      81,   12,   12,   12, 0x08,
      97,   12,   12,   12, 0x08,
     116,   12,   12,   12, 0x08,
     123,   12,   12,   12, 0x08,
     130,   12,   12,   12, 0x08,
     152,  142,   12,   12, 0x08,
     187,  171,   12,   12, 0x08,
     205,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Main_Window[] = {
    "Main_Window\0\0index\0filler(int)\0SEARCH()\0"
    "AlphaSort()\0RSort()\0ADDCART()\0VIEWCART()\0"
    "PUSHBUYBUTTON()\0PUSHREMOVEBUTTON()\0"
    "SAVE()\0QUIT()\0ADDREVIEW()\0prodIndex\0"
    "ProductChange(int)\0usercartcounter\0"
    "ReviewChange(int)\0displayReviews()\0"
};

void Main_Window::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Main_Window *_t = static_cast<Main_Window *>(_o);
        switch (_id) {
        case 0: _t->filler((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->SEARCH(); break;
        case 2: _t->AlphaSort(); break;
        case 3: _t->RSort(); break;
        case 4: _t->ADDCART(); break;
        case 5: _t->VIEWCART(); break;
        case 6: _t->PUSHBUYBUTTON(); break;
        case 7: _t->PUSHREMOVEBUTTON(); break;
        case 8: _t->SAVE(); break;
        case 9: _t->QUIT(); break;
        case 10: _t->ADDREVIEW(); break;
        case 11: _t->ProductChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->ReviewChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->displayReviews(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Main_Window::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Main_Window::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Main_Window,
      qt_meta_data_Main_Window, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Main_Window::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Main_Window::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Main_Window::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Main_Window))
        return static_cast<void*>(const_cast< Main_Window*>(this));
    return QWidget::qt_metacast(_clname);
}

int Main_Window::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
