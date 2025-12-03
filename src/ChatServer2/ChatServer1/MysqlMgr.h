#pragma once
#include "const.h"
#include "MysqlDao.h"
#include "data.h"
class MysqlMgr : public Singleton<MysqlMgr>
{
	friend class Singleton<MysqlMgr>;
public:
	~MysqlMgr();
	int RegUser(const std::string& name, const std::string& email, const std::string& pwd);
	bool checkEmail(const std::string& name, const std::string& email);
	bool updatePwd(const std::string& email, const std::string& newPwd);
	bool selectPwd(const std::string& email, UserInfo& userInfo);
	bool AddFriendApply(const int& from, const int& to);
	bool GetApplyList(int touid, std::vector<std::shared_ptr<ApplyInfo>>& applyList, int begin, int limit = 10);
	bool GetFriendList(int self_uid, std::vector<std::shared_ptr<UserInfo>>& friendList);
	bool AuthFriendApply(const int& from, const int& to);
	bool AddFriend(const int& from, const int& to, const std::string& back);
	std::shared_ptr<UserInfo> GetUser(int uid);
	std::shared_ptr<UserInfo> GetUser(const std::string& name);
private:
	MysqlMgr();
	MysqlDao _dao;
};

