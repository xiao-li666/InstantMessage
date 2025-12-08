/****************************************************************************
** Meta object code from reading C++ file 'chatdialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../chatdialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'chatdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ChatDialog_t {
    QByteArrayData data[31];
    char stringdata0[575];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ChatDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ChatDialog_t qt_meta_stringdata_ChatDialog = {
    {
QT_MOC_LITERAL(0, 0, 10), // "ChatDialog"
QT_MOC_LITERAL(1, 11, 23), // "slot_uploading_chatUser"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 14), // "slot_side_chat"
QT_MOC_LITERAL(4, 51, 17), // "slot_side_contact"
QT_MOC_LITERAL(5, 69, 17), // "slot_text_changed"
QT_MOC_LITERAL(6, 87, 3), // "str"
QT_MOC_LITERAL(7, 91, 25), // "slot_loading_contact_user"
QT_MOC_LITERAL(8, 117, 17), // "slot_friend_apply"
QT_MOC_LITERAL(9, 135, 31), // "std::shared_ptr<AddFriendApply>"
QT_MOC_LITERAL(10, 167, 20), // "slot_add_auth_friend"
QT_MOC_LITERAL(11, 188, 25), // "std::shared_ptr<AuthInfo>"
QT_MOC_LITERAL(12, 214, 13), // "slot_auth_rsp"
QT_MOC_LITERAL(13, 228, 24), // "std::shared_ptr<AuthRsp>"
QT_MOC_LITERAL(14, 253, 19), // "slot_jump_chat_item"
QT_MOC_LITERAL(15, 273, 27), // "std::shared_ptr<SearchInfo>"
QT_MOC_LITERAL(16, 301, 2), // "si"
QT_MOC_LITERAL(17, 304, 21), // "slot_friend_info_page"
QT_MOC_LITERAL(18, 326, 25), // "std::shared_ptr<UserInfo>"
QT_MOC_LITERAL(19, 352, 9), // "user_info"
QT_MOC_LITERAL(20, 362, 22), // "slot_friend_apply_page"
QT_MOC_LITERAL(21, 385, 33), // "slot_jump_chat_item_from_info..."
QT_MOC_LITERAL(22, 419, 17), // "slot_item_clicked"
QT_MOC_LITERAL(23, 437, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(24, 454, 4), // "item"
QT_MOC_LITERAL(25, 459, 25), // "slot_append_send_chat_msg"
QT_MOC_LITERAL(26, 485, 29), // "std::shared_ptr<TextChatData>"
QT_MOC_LITERAL(27, 515, 7), // "msgdata"
QT_MOC_LITERAL(28, 523, 18), // "slot_text_chat_msg"
QT_MOC_LITERAL(29, 542, 28), // "std::shared_ptr<TextChatMsg>"
QT_MOC_LITERAL(30, 571, 3) // "msg"

    },
    "ChatDialog\0slot_uploading_chatUser\0\0"
    "slot_side_chat\0slot_side_contact\0"
    "slot_text_changed\0str\0slot_loading_contact_user\0"
    "slot_friend_apply\0std::shared_ptr<AddFriendApply>\0"
    "slot_add_auth_friend\0std::shared_ptr<AuthInfo>\0"
    "slot_auth_rsp\0std::shared_ptr<AuthRsp>\0"
    "slot_jump_chat_item\0std::shared_ptr<SearchInfo>\0"
    "si\0slot_friend_info_page\0"
    "std::shared_ptr<UserInfo>\0user_info\0"
    "slot_friend_apply_page\0"
    "slot_jump_chat_item_from_infopage\0"
    "slot_item_clicked\0QListWidgetItem*\0"
    "item\0slot_append_send_chat_msg\0"
    "std::shared_ptr<TextChatData>\0msgdata\0"
    "slot_text_chat_msg\0std::shared_ptr<TextChatMsg>\0"
    "msg"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ChatDialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x08 /* Private */,
       3,    0,   90,    2, 0x08 /* Private */,
       4,    0,   91,    2, 0x08 /* Private */,
       5,    1,   92,    2, 0x08 /* Private */,
       7,    0,   95,    2, 0x08 /* Private */,
       8,    1,   96,    2, 0x0a /* Public */,
      10,    1,   99,    2, 0x0a /* Public */,
      12,    1,  102,    2, 0x0a /* Public */,
      14,    1,  105,    2, 0x0a /* Public */,
      17,    1,  108,    2, 0x0a /* Public */,
      20,    0,  111,    2, 0x0a /* Public */,
      21,    1,  112,    2, 0x0a /* Public */,
      22,    1,  115,    2, 0x0a /* Public */,
      25,    1,  118,    2, 0x0a /* Public */,
      28,    1,  121,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,    2,
    QMetaType::Void, 0x80000000 | 11,    2,
    QMetaType::Void, 0x80000000 | 13,    2,
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::Void, 0x80000000 | 18,   19,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 18,   16,
    QMetaType::Void, 0x80000000 | 23,   24,
    QMetaType::Void, 0x80000000 | 26,   27,
    QMetaType::Void, 0x80000000 | 29,   30,

       0        // eod
};

void ChatDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ChatDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slot_uploading_chatUser(); break;
        case 1: _t->slot_side_chat(); break;
        case 2: _t->slot_side_contact(); break;
        case 3: _t->slot_text_changed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->slot_loading_contact_user(); break;
        case 5: _t->slot_friend_apply((*reinterpret_cast< std::shared_ptr<AddFriendApply>(*)>(_a[1]))); break;
        case 6: _t->slot_add_auth_friend((*reinterpret_cast< std::shared_ptr<AuthInfo>(*)>(_a[1]))); break;
        case 7: _t->slot_auth_rsp((*reinterpret_cast< std::shared_ptr<AuthRsp>(*)>(_a[1]))); break;
        case 8: _t->slot_jump_chat_item((*reinterpret_cast< std::shared_ptr<SearchInfo>(*)>(_a[1]))); break;
        case 9: _t->slot_friend_info_page((*reinterpret_cast< std::shared_ptr<UserInfo>(*)>(_a[1]))); break;
        case 10: _t->slot_friend_apply_page(); break;
        case 11: _t->slot_jump_chat_item_from_infopage((*reinterpret_cast< std::shared_ptr<UserInfo>(*)>(_a[1]))); break;
        case 12: _t->slot_item_clicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 13: _t->slot_append_send_chat_msg((*reinterpret_cast< std::shared_ptr<TextChatData>(*)>(_a[1]))); break;
        case 14: _t->slot_text_chat_msg((*reinterpret_cast< std::shared_ptr<TextChatMsg>(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ChatDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_ChatDialog.data,
    qt_meta_data_ChatDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ChatDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ChatDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ChatDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int ChatDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
