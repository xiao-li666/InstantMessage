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

std::shared_ptr<UserInfo> MysqlMgr::GetUser(int uid)
{
	return _dao.GetUser(uid);
}

