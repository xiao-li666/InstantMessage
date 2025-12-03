#include "MysqlMgr.h"

MysqlMgr::MysqlMgr()
{

}

MysqlMgr::~MysqlMgr()
{
}

int MysqlMgr::RegUser(const std::string& name, const std::string& email, const std::string& pwd)
{
	return _dao.RegUser(name, email, pwd);
}

bool MysqlMgr::checkEmail(const std::string& name, const std::string& email)
{
	return _dao.checkEmail(name, email);
}

bool MysqlMgr::updatePwd(const std::string& email, const std::string& newPwd)
{
	return _dao.updatePwd(email, newPwd);
}

bool MysqlMgr::selectPwd(const std::string& email, UserInfo& userInfo)
{
	return _dao.selectPwd(email,userInfo);
}

bool MysqlMgr::AddFriendApply(const int& from, const int& to)
{
	return _dao.AddFriendApply(from, to);
}

bool MysqlMgr::GetApplyList(int touid, std::vector<std::shared_ptr<ApplyInfo>>& applyList, int begin, int limit)
{
	return _dao.GetApplyList(touid, applyList, begin, limit);
}

bool MysqlMgr::GetFriendList(int self_uid, std::vector<std::shared_ptr<UserInfo>>& friendList)
{
	return _dao.GetFriendList(self_uid, friendList);
}

bool MysqlMgr::AuthFriendApply(const int& from, const int& to)
{
	return _dao.AuthFriendApply(from, to);
}

bool MysqlMgr::AddFriend(const int& from, const int& to, const std::string& back)
{
	return _dao.AddFriend(from, to, back);
}

std::shared_ptr<UserInfo> MysqlMgr::GetUser(int uid)
{
	return _dao.GetUser(uid);
}

std::shared_ptr<UserInfo> MysqlMgr::GetUser(const std::string& name)
{
	return _dao.GetUser(name);
}

