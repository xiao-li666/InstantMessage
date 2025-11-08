#ifndef GLOBAL_H
#define GLOBAL_H

#include <QWidget>
#include <functional>
#include "QStyle"
#include <QRegularExpression>
#include <memory>
#include <iostream>
#include <mutex>
#include <QString>
#include <QUrl>
#include <QObject>
#include <QNetworkAccessManager>//网络guanli
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
#include <QNetworkReply>
#include <QDir>
#include <QSettings>

//功能id
enum ReqId{
    ID_GET_VARIFY_CODE = 1001,//获取验证码
    ID_REG_USER = 1002,//注册用户
    ID_RESET_PASS = 1003,//重置密码
    ID_LOGIN = 1004, //登录
    ID_CHAT_LOGIN = 1005, //登录聊天服务器
    ID_CHAT_LOGIN_RSP = 1006,//登录聊天服务器回包
};
//功能模块
enum Modules{
    REGISTERMOD = 0, //注册
    RESETPASSWORD = 1, //重置密码
    LOGIN = 2, //登录
};

//
enum ErrorCodes{
    SUCCESS = 0,
    ERR_JSON = 1,//json解析失败
    ERR_NETWORK = 2, //网络错误
    VarifyExpire = 1003, //验证码超时
    VarifyCodeError = 1004, //验证码错误
    UserExits = 1005, //用户不存在
    PassWdErr = 1006,//密码错误
    EmailNotMatch = 1007,//邮箱不匹配
    PasswdUpFailed = 1008,//更新密码失败
    UserNoExits = 1009,//用户不存在
};

enum TipErr{
    TIP_SUCCESS = 0,
    TIP_EMAIL_ERR = 1,
    TIP_PWD_ERR = 2,
    TIP_CONFIRM_ERR = 3,//确认密码错误
    TIP_PWD_CONFIRM = 4,//密码不匹配
    TIP_VARIFY_ERR = 5,
    TIP_USER_ERR = 6
};

enum ClickLbState{
    Normal = 0,
    Selected = 1
};

struct ServerInfo{
    QString Host;
    QString Port;
    QString Token;
    int Uid;
};

//聊天界面的集中模式
enum ChatUIMode{
    SearchMode,//搜索模式
    ChatMode,//聊天模式
    ContactMode,//联系模式
};

enum ListItemType{
    CHAT_USER_ITEM, //聊天用户
    CONTACT_USER_ITEM, //联系人用户
    SEARCH_USER_ITEM, //搜索到的用户
    ADD_USER_TIP_ITEM, //提示添加用户
    INVALID_ITEM, //不可点击条目
    GROUP_TIP_ITEM, //分组提示条目
};

enum class ChatRole
{
    Self,
    Other
};

struct MsgInfo{
    QString msgFlag;
    QString context;
    QPixmap pixmap;
};

/*
    用来刷新 qss
*/
extern std::function<void(QWidget*)> repolish;

extern QString gateUrlPrefix;

//密码加密,异或字符串
extern std::function<QString(QString)> xorString;

#endif // GLOBAL_H
