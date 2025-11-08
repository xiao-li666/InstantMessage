#include "LogicSystem.h"
#include "MysqlMgr.h"
#include "data.h"
#include "StatusGrpcClient.h"

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

	//从状态服务器获得token匹配是否正确
	auto rsp = StatusGrpcClient::GetInstance()->Login(uid, token);
	Json::Value rtvalue;
	Defer defer([this, &rtvalue, session]() {
		std::string return_str = rtvalue.toStyledString();
		session->Send(return_str, ID_CHAT_LOGIN_RSP);
		});
	rtvalue["error"] = rsp.error();
	if (rsp.error() != ErrorCodes::Success) {
		return;
	}

	//内存中查用户信息
	auto find_iter = _users.find(uid);
	std::shared_ptr<UserInfo> user_info = std::make_shared<UserInfo>();
	if (find_iter == _users.end()) {
		//查询数据库
		user_info = MysqlMgr::GetInstance()->GetUser(uid);
		if (user_info == nullptr) {
			rtvalue["error"] = ErrorCodes::UidInvalid;
			return;
		}
		_users.insert({ uid, user_info });
	}
	else {
		user_info = find_iter->second;
	}
	std::cout << "has send login message to client" << std::endl;
	rtvalue["uid"] = uid;
	rtvalue["token"] = token;
	rtvalue["name"] = user_info->name;
}
