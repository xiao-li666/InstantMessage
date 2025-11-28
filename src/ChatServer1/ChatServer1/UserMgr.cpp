#include "UserMgr.h"
#include "CSession.h"
#include "RedisMgr.h"
UserMgr::UserMgr()
{
}
UserMgr::~UserMgr()
{
	_userSessionMap.clear();
}

void UserMgr::AddUserSession(int uid, std::shared_ptr<CSession> session)
{
	std::lock_guard<std::mutex> lock(_mutex);
	_userSessionMap[uid] = session;
}

void UserMgr::RemoveUserSession(int uid)
{
	std::lock_guard<std::mutex> lock(_mutex);
	_userSessionMap.erase(uid);
}

std::shared_ptr<CSession> UserMgr::GetUserSession(int uid)
{
	std::lock_guard<std::mutex> lock(_mutex);
	auto iter = _userSessionMap.find(uid);
	if (iter == _userSessionMap.end()) {
		return nullptr;
	}
	return iter->second;
}
