#ifndef USERMGR_H
#define USERMGR_H
#include <QObject>
#include <memory>
#include <singleton.h>
#include "userdata.h"

class UserMgr : public QObject ,public Singleton<UserMgr>, public std::enable_shared_from_this<UserMgr>
{
    Q_OBJECT
public:
    friend class Singleton<UserMgr>;
    ~UserMgr();
    //void SetName(QString name);
    QString GetName();
    void SetUid(int uid);
    int GetUid();
    void SetToken(QString token);
    void SetUserInfo(std::shared_ptr<UserInfo> userinfo);
    std::shared_ptr<UserInfo> GetUserInfo();
    QString GetIcon();

    std::vector<std::shared_ptr<ApplyInfo>> GetApplyList();

    std::vector<std::shared_ptr<FriendInfo>> GetChatListPerPage();
    bool IsLoadChatFin();
    void UpdateChatLoadedCount();
    std::vector<std::shared_ptr<FriendInfo>> GetConListPerPage();
    bool IsLoadConFin();
    void UpdateContactLoadedCount();

    void AppendApplyList(QJsonArray array);
    void AppendFriendList(QJsonArray array);

    bool CheckFriendById(int uid);
    void AddFriend(std::shared_ptr<AuthRsp> auth_rsp);
    void AddFriend(std::shared_ptr<AuthInfo> auth_info);
    std::shared_ptr<FriendInfo> GetFriendById(int uid);
    bool AlreadyApply(int uid);
    void SetApply(std::shared_ptr<ApplyInfo>);
    void DelApply(std::shared_ptr<ApplyInfo>);
private:
    UserMgr();
    std::shared_ptr<UserInfo> _user_info;
    std::vector<std::shared_ptr<ApplyInfo>> _apply_list;
    std::vector<std::shared_ptr<FriendInfo>> _friend_list;
    QMap<int, std::shared_ptr<FriendInfo>> _friend_map;
    QString _token;
    int _chat_loaded;
    int _contact_loaded;
};

#endif // USERMGR_H
