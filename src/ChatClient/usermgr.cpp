#include "usermgr.h"
UserMgr::UserMgr() {}

UserMgr::~UserMgr()
{

}

QString UserMgr::GetName()
{
    return _user_info->_name;
}

void UserMgr::SetUid(int uid)
{
    _user_info->_uid = uid;
}

int UserMgr::GetUid()
{
    return _user_info->_uid;
}

void UserMgr::SetToken(QString token)
{
    _token = token;
}

void UserMgr::SetUserInfo(std::shared_ptr<UserInfo> userinfo)
{
    _user_info = userinfo;
}

std::vector<std::shared_ptr<ApplyInfo> > UserMgr::GetApplyList()
{
    return _apply_list;
}

std::vector<std::shared_ptr<FriendInfo> > UserMgr::GetConListPerPage()
{
    std::vector<std::shared_ptr<FriendInfo>> friend_list;
    int begin = _contact_loaded;
    int end = begin + CHAT_COUNT_PER_PAGE;

    if (begin >= _friend_list.size()) {
        return friend_list;
    }

    if (end > _friend_list.size()) {
        friend_list = std::vector<std::shared_ptr<FriendInfo>>(_friend_list.begin() + begin, _friend_list.end());
        return friend_list;
    }


    friend_list = std::vector<std::shared_ptr<FriendInfo>>(_friend_list.begin() + begin, _friend_list.begin() + end);
    return friend_list;
}

void UserMgr::UpdateContactLoadedCount()
{
    int begin = _contact_loaded;
    int end = begin + CHAT_COUNT_PER_PAGE;

    if (begin >= _friend_list.size()) {
        return;
    }

    if (end > _friend_list.size()) {
        _contact_loaded = _friend_list.size();
        return;
    }

    _contact_loaded = end;
}

void UserMgr::AppendApplyList(QJsonArray array)
{
    for(const QJsonValue &value : array){
        auto name = value["name"].toString();
        auto desc = value["desc"].toString();
        auto icon = value["icon"].toString();
        auto nick = value["nick"].toString();
        auto sex = value["sex"].toInt();
        auto uid = value["uid"].toInt();
        auto status = value["status"].toInt();
        auto info = std::make_shared<ApplyInfo>(uid, name, desc, icon, nick, sex, status);
        _apply_list.push_back(info);
    }
}

bool UserMgr::IsLoadConFin()
{
    if (_contact_loaded >= _friend_list.size()) {
        return true;
    }

    return false;
}

bool UserMgr::IsLoadChatFin()
{
    if (_chat_loaded >= _friend_list.size()) {
        return true;
    }

    return false;
}

bool UserMgr::CheckFriendById(int uid)
{
    auto iter = _friend_map.find(uid);
    if(iter == _friend_map.end()){
        return false;
    }

    return true;
}

bool UserMgr::AlreadyApply(int uid)
{
    for(auto&apply : _apply_list){
        if(apply->_uid == uid)return true;
    }
    //_apply_list.emplace_back(uid);
    return false;
}

void UserMgr::SetApply(std::shared_ptr<ApplyInfo> apply)
{
    _apply_list.push_back(apply);
}

void UserMgr::DelApply(std::shared_ptr<ApplyInfo> apply)
{
    for(auto it = _apply_list.begin(); it != _apply_list.end(); it++){
        if((*it)->_uid == apply->_uid){
            _apply_list.erase(it);
            return;
        }
    }
}

