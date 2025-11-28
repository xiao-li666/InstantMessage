#pragma once
#include "Singleton.h"
#include <queue>
#include <thread>
#include "CSession.h"
#include <map>
#include <functional>
#include "const.h"
#include <json/json.h>
#include <json/value.h>
#include <json/reader.h>
#include <unordered_map>
struct UserInfo;
class CServer;
typedef std::function<void(std::shared_ptr<CSession>, const size_t& msgId, const std::string& msgData)> FunCallBack;
class LogicSystem : public Singleton<LogicSystem>
{
	friend class Singleton<LogicSystem>;
public:
	~LogicSystem();
	void PostMsgToQue(std::shared_ptr <LogicNode> msg);
private:
	LogicSystem();
	void DealMsg();
	void RegisterCallBacks();
	void LoginHandler(std::shared_ptr<CSession> session, const size_t& msg_id, const std::string& msg_data);

	bool GetBaseInfo(std::string base_key, int uid, std::shared_ptr<UserInfo>& userinfo);

	bool _b_stop;

	std::queue<std::shared_ptr<LogicNode>> _msgQue;
	std::mutex _msgQueMtx;
	std::condition_variable _consume;

	std::map<std::size_t, FunCallBack> _funCallBacks;
	std::mutex _mutex;
	std::thread _workThread;

	std::map<int, std::shared_ptr<UserInfo>> _users;
};

