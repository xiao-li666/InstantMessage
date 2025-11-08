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
	std::shared_ptr<UserInfo> GetUser(int uid);
private:
	MysqlMgr();
	MysqlDao _dao;
};

