#include "LogicSystem.h"
#include "MysqlMgr.h"
#include "data.h"
#include "StatusGrpcClient.h"
#include "ChatGrpcClient.h"
#include "UserMgr.h"

LogicSystem::LogicSystem() : _b_stop(false)
{
	RegisterCallBacks();
	_workThread = std::thread(&LogicSystem::DealMsg, this);
}
LogicSystem::~LogicSystem()
{
	_b_stop = true;
	_consume.notify_one();
	_workThread.join();
}

void LogicSystem::PostMsgToQue(std::shared_ptr<LogicNode> msg)
{
	std::unique_lock<std::mutex> lock(_msgQueMtx);
	if (_msgQue.size() > MAX_SENDQUE) {
		std::cout << "send queue size is MAX_SENDQUE" << std::endl;
		return;
	}
	_msgQue.push(msg);
	if (_msgQue.size() == 1) {
		lock.unlock();
		_consume.notify_one();
	}
}
void LogicSystem::DealMsg()
{
	for (;;) {
		std::unique_lock<std::mutex> lock(_msgQueMtx);
		while (_msgQue.empty() && !_b_stop) {
			_consume.wait(lock);
		}
		//判断是否为关闭状态，把所有逻辑执行完后则退出循环
		if (_b_stop) {
			while (!_msgQue.empty()) {
				auto msgnode = _msgQue.front();
				std::cout << "recv_msg id  is " << msgnode->_recvnode->_msgId << std::endl;
				auto iter = _funCallBacks.find(msgnode->_recvnode->_msgId);
				if (iter == _funCallBacks.end()) {
					_msgQue.pop();
					return;
				}
				iter->second(msgnode->_session, msgnode->_recvnode->_msgId, std::string(msgnode->_recvnode->_data,msgnode->_recvnode->_curlen));
				_msgQue.pop();
			}
			break;
		}
		auto msgnode = _msgQue.front();
		std::cout << "recv_msg id  is " << msgnode->_recvnode->_msgId << std::endl;
		auto iter = _funCallBacks.find(msgnode->_recvnode->_msgId);
		if (iter == _funCallBacks.end()) {
			std::cout << "msg id [" << msgnode->_recvnode->_msgId << "] handler not found" << std::endl;
			_msgQue.pop();
			continue;
		}
		iter->second(msgnode->_session, msgnode->_recvnode->_msgId, std::string(msgnode->_recvnode->_data, msgnode->_recvnode->_curlen));
		_msgQue.pop();
	}
}

void LogicSystem::RegisterCallBacks()
{
	_funCallBacks[ID_CHAT_LOGIN] = std::bind(&LogicSystem::LoginHandler, this,
		std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	_funCallBacks[ID_SEARCH_USER_REQ] = std::bind(&LogicSystem::SearchUserHandler, this,
		std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	_funCallBacks[ID_ADD_FRIEND_REQ] = std::bind(&LogicSystem::AddFriendApplyHandler, this,
		std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
}

void LogicSystem::LoginHandler(std::shared_ptr<CSession> session, const size_t& msg_id, const std::string& msg_data)
{
	Json::Reader reader;
	Json::Value root;
	reader.parse(msg_data, root);
	auto uid = root["uid"].asInt();
	auto token = root["token"].asString();
	std::cout << "user login uid is  " << uid << " user token  is "
		<< token << std::endl;

	Json::Value rtvalue;
	Defer defer([this, &rtvalue, session]() {
		std::string return_str = rtvalue.toStyledString();
		session->Send(return_str, ID_CHAT_LOGIN_RSP);
		});
	
	//在redis中查找uid和token
	std::string uidStr = std::to_string(uid);
	//这里在redis中存储uid和token时，用token的前缀+uid作为key值，也是一种安保方法
	std::string tokenKey = USERTOKENPREFIX + uidStr;
	std::string tokenValue = "";
	if (!RedisMgr::GetInstance()->Get(tokenKey, tokenValue)) {
		//没有查询到
		rtvalue["error"] = ErrorCodes::UidInvalid;
	}
	else if (tokenValue != token) {
		//查询到但是token不对
		rtvalue["error"] = ErrorCodes::TokenInvalid;
	}
	else {
		rtvalue["error"] = ErrorCodes::Success;
	}

	//查用户信息,每个服务器都需要保存一份用户的基本信息在redis中，避免每次都去mysql中查询
	std::shared_ptr<UserInfo> user_info = std::make_shared<UserInfo>();
	std::string baseKey = USER_BASE_INFO + uidStr;
	if (!GetBaseInfo(baseKey, uid, user_info)) {
		//没有查询到用户信息
		rtvalue["error"] = ErrorCodes::UidInvalid;
		return;
	}
	std::cout << "has send login message to client" << std::endl;
	rtvalue["uid"] = uid;
	rtvalue["token"] = token;
	rtvalue["email"] = user_info->email;
	rtvalue["pwd"] = user_info->pwd;
	rtvalue["name"] = user_info->name;
	rtvalue["nick"] = user_info->nick;
	rtvalue["desc"] = user_info->desc;
	rtvalue["sex"] = user_info->sex;
	rtvalue["icon"] = user_info->icon;

	//获取申请好友列表
	std::vector<std::shared_ptr<ApplyInfo>> applyInfos;
	auto b_apply = GetFriendApplyInfo(uid, applyInfos);
	if (b_apply) {
		for (auto& apply : applyInfos) {
			Json::Value obj;
			obj["uid"] = apply->_uid;
			obj["name"] = apply->_name;
			obj["nick"] = apply->_nick;
			obj["desc"] = apply->_desc;
			obj["sex"] = apply->_sex;
			obj["status"] = apply->_status;
			obj["icon"] = apply->_icon;
			rtvalue["apply_list"].append(obj);
		}
	}
	//从数据库中获取用户的好友列表，群组列表等信息，后续再添加

	//登录成功后，更新该服务器的在线用户数量
	auto server_name = ConfigMgr::GetInstance()["SelfServer"]["Name"];
	auto res = RedisMgr::GetInstance()->HGet(LOGIN_COUNT, server_name);
	int count = 0;
	if (!res.empty()) {
		count = std::stoi(res);
	}
	count++;
	//更新在线用户数量
	RedisMgr::GetInstance()->HSet(LOGIN_COUNT, server_name, std::to_string(count));

	std::cout << "server " << server_name << " login user count is " << count << std::endl;

	//session绑定uid
	session->SetUserUid(uid);
	//为用户设置ip和server的名字,可以通过当前用户的uid找到对应的服务器地址
	std::string ipKey = USERIPPREFIX + uidStr;
	RedisMgr::GetInstance()->Set(ipKey, server_name);
	//将uid和session绑定在一起，方便以后的踢人操作
	UserMgr::GetInstance()->AddUserSession(uid, session);
	return;
}

void LogicSystem::SearchUserHandler(std::shared_ptr<CSession> session, const size_t& msg_id, const std::string& msg_data)
{
	Json::Reader reader;
	Json::Value root;
	reader.parse(msg_data, root);
	auto uid = root["uid"].asString();
	std::cout << "search user uid is  " << uid << std::endl;
	Json::Value rtvalue;

	Defer deder([this, session, &rtvalue]() {
		std::string returnStr = rtvalue.toStyledString();
		session->Send(returnStr, ID_SEARCH_USER_RSP);
		});

	std::shared_ptr<UserInfo> user_info = std::make_shared<UserInfo>();
	if (!isPureDigit(uid)) {
		//uid不是纯数字，说明是email
		if (!GetUserByName(uid, user_info)) {
			//没有查询到用户信息
			rtvalue["error"] = ErrorCodes::UserNoExits;
			return;
		}
	}
	else {
		int search_uid = std::stoi(uid);
		//查询用户信息
		std::string baseKey = USER_BASE_INFO + uid;
		if (!GetBaseInfo(baseKey, search_uid, user_info)) {
			//没有查询到用户信息
			rtvalue["error"] = ErrorCodes::UserNoExits;
			return;
		}
	}
	rtvalue["error"] = ErrorCodes::Success;
	rtvalue["uid"] = user_info->uid;
	rtvalue["name"] = user_info->name;
	rtvalue["nick"] = user_info->nick;
	rtvalue["desc"] = user_info->desc;
	rtvalue["sex"] = user_info->sex;
	rtvalue["icon"] = user_info->icon;
	return;
}

void LogicSystem::AddFriendApplyHandler(std::shared_ptr<CSession> session, const size_t& msg_id, const std::string& msg_data)
{
	Json::Reader reader;
	Json::Value root;
	reader.parse(msg_data, root);
	auto from_uid = root["uid"].asInt();
	auto to_uid = root["touid"].asInt();
	auto applyName = root["applyname"].asString();
	std::cout << "add friend apply from uid is  " << from_uid << " to uid is " << to_uid << std::endl;

	Json::Value rtvalue;
	rtvalue["error"] = ErrorCodes::Success;
	Defer defer([this, &rtvalue, session]() {
		std::string return_str = rtvalue.toStyledString();
		session->Send(return_str, ID_ADD_FRIEND_RSP);
		});

	//先更新数据库
	MysqlMgr::GetInstance()->AddFriendApply(from_uid, to_uid);

	//查询redis中to_uid所在的服务器ip
	std::string to_ip_key = USERIPPREFIX + std::to_string(to_uid);
	std::string to_ip_value = "";
	if (!RedisMgr::GetInstance()->Get(to_ip_key, to_ip_value)) {
		//没有查询到，说明不在线，直接返回成功
		std::cout << "to uid " << to_uid << " not online" << std::endl;
		return;
	}
	//通知对应的服务器，有好友申请
	auto& conf = ConfigMgr::GetInstance();
	auto self_server_name = conf["SelfServer"]["Name"];
	if (to_ip_value == self_server_name) {
		auto session = UserMgr::GetInstance()->GetUserSession(to_uid);
		//在同一个服务器
		if (session) {
			Json::Value notifyValue;
			notifyValue["error"] = ErrorCodes::Success;
			notifyValue["applyuid"] = from_uid;
			notifyValue["name"] = applyName;
			notifyValue["desc"] = "";
			std::string notifyStr = notifyValue.toStyledString();
			session->Send(notifyStr, ID_NOTIFY_ADD_FRIEND_REQ);
		}
		return;
	}
	//不在同一个服务器，通知对应的服务器
	std::string base_key = USER_BASE_INFO + std::to_string(from_uid);
	auto applyUserInfo = std::make_shared<UserInfo>();
	bool b_info = GetBaseInfo(base_key, from_uid, applyUserInfo);
	AddFriendReq req;
	req.set_touid(to_uid);
	req.set_applyuid(from_uid);
	req.set_name(applyName);
	req.set_desc("");
	if (b_info) {
		req.set_icon(applyUserInfo->icon);
		req.set_nick(applyUserInfo->nick);
		req.set_sex(applyUserInfo->sex);
	}

	ChatGrpcClient::GetInstance()->NotifyAddFriend(to_ip_value, req);
}

bool LogicSystem::GetBaseInfo(std::string base_key, int uid, std::shared_ptr<UserInfo>& userinfo)
{
	//先查找redis,redis中没有查到，再查mysql，查到后存入redis
	std::string infoStr = "";
	if (RedisMgr::GetInstance()->Get(base_key, infoStr)) {
		//redis中查询到用户的登录信息
		Json::Reader reader;
		Json::Value root;
		if (!reader.parse(infoStr, root)) {
			return false;
		}
		userinfo->uid = root["uid"].asInt();
		userinfo->name = root["name"].asString();
		userinfo->pwd = root["pwd"].asString();
		userinfo->email = root["email"].asString();
		userinfo->nick = root["nick"].asString();
		userinfo->desc = root["desc"].asString();
		userinfo->sex = root["sex"].asInt();
		userinfo->icon = root["icon"].asString();
	}
	else {
		//redis中没有查询到用户的登录信息，从mysql中查询
		std::shared_ptr<UserInfo> user_info = nullptr;
		user_info = MysqlMgr::GetInstance()->GetUser(uid);
		if (user_info == nullptr) {
			return false;
		}
		userinfo = user_info;
		//将用户的登录信息存入redis中
		Json::Value root;
		root["uid"] = userinfo->uid;
		root["name"] = userinfo->name;
		root["pwd"] = userinfo->pwd;
		root["email"] = userinfo->email;
		root["nick"] = userinfo->nick;
		root["desc"] = userinfo->desc;
		root["sex"] = userinfo->sex;
		root["icon"] = userinfo->icon;
		RedisMgr::GetInstance()->Set(base_key, root.toStyledString());
	}
	return true;
}

bool LogicSystem::GetUserByName(std::string name, std::shared_ptr<UserInfo>& userinfo)
{
	//直接在mysql中查找
	userinfo = MysqlMgr::GetInstance()->GetUser(name);
	if (userinfo == nullptr) {
		return false;
	}
	return true;
}

bool LogicSystem::GetFriendApplyInfo(int uid, std::vector<std::shared_ptr<ApplyInfo>>& applyInfos)
{
	return MysqlMgr::GetInstance()->GetApplyList(uid,applyInfos, 0, 10);
}

bool LogicSystem::isPureDigit(const std::string& str)
{
	for (char c : str) {
		if (!isdigit(c)) {
			return false;
		}
	}
	return true;
}
