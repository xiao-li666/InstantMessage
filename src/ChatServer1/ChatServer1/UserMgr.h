#pragma once
#include "Singleton.h"
#include <unordered_map>
#include <memory>
#include <mutex>

/* 
	用户管理类，管理在线用户会话
*/

class CSession;
class UserMgr : public Singleton<UserMgr>
{
public:
	friend class Singleton<UserMgr>;
	~UserMgr();
	//添加用户会话
	void AddUserSession(int uid, std::shared_ptr<CSession> session);
	//删除用户会话
	void RemoveUserSession(int uid);
	//获取用户会话
	std::shared_ptr<CSession> GetUserSession(int uid);
private:
	UserMgr();
	std::unordered_map<int, std::shared_ptr<CSession>> _userSessionMap;
	std::mutex _mutex;
};

