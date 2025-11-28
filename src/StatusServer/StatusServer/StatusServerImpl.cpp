#include "StatusServerImpl.h"
#include "ConfigMgr.h"
#include "RedisMgr.h"


std::string generate_unique_string() {
	// 创建UUID对象
	boost::uuids::uuid uuid = boost::uuids::random_generator()();
	// 将UUID转换为字符串
	std::string unique_string = to_string(uuid);
	return unique_string;
}

StatusServerImpl::StatusServerImpl()
{
	auto& conf = ConfigMgr::GetInstance();
	auto server_list = conf["ChatServers"]["Name"];

	std::vector<std::string> words;

	std::stringstream ss(server_list);
	std::string word;

	while (std::getline(ss, word, ',')) {
		words.push_back(word);
	}

	for (auto& word : words) {
		if (conf[word]["Name"].empty()) {
			continue;
		}
		ChatServer server;
		server.name = conf[word]["Name"];
		server.host = conf[word]["Host"];
		server.port = conf[word]["Port"];
		_servers[server.name] = server;
	}
}

StatusServerImpl::~StatusServerImpl()
{
}

Status StatusServerImpl::GetChatServer(ServerContext* context, const GetChatServerReq* request, GetChatServerRsp* reply)
{
	std::string prefix("xiaoli status server has received: ");
	const auto& server = getChatServer();
	reply->set_host(server.host);
	reply->set_port(server.port);
	reply->set_error(ErrorCodes::Success);
	reply->set_token(generate_unique_string());
	insertToken(request->uid(), reply->token());
	std::cout << "GetChatServer has send reply" << std::endl;
	return Status::OK;
}

Status StatusServerImpl::Login(ServerContext* context, const LoginReq* request, LoginRsp* reply)
{
	auto uid = request->uid();
	auto token = request->token();
	std::cout << "Login has send LoginReq uid is " << uid << " token is " << token << std::endl;
	//在redis中查找uid和token
	std::string uidStr = std::to_string(uid);
	//这里在redis中存储uid和token时，用token的前缀+uid作为key值，也是一种安保方法
	std::string tokenKey = USERTOKENPREFIX + uidStr;
	std::string tokenValue = "";
	if (!RedisMgr::GetInstance()->Get(tokenKey, tokenValue)) {
		//没有查询到
		reply->set_error(ErrorCodes::UidInvalid);
	}
	else if(tokenValue != token){
		//查询到但是token不对
		reply->set_error(ErrorCodes::TokenInvalid);
	}
	else {
		reply->set_error(ErrorCodes::Success);
	}
	reply->set_uid(uid);
	reply->set_token(token);
	std::cout << "Login has send reply" << std::endl;
	return Status::OK;
}

void StatusServerImpl::insertToken(int uid, std::string token)
{
	//插入到redis中
	RedisMgr::GetInstance()->Set(USERTOKENPREFIX+std::to_string(uid), token);
}

ChatServer StatusServerImpl::getChatServer()
{
	std::lock_guard<std::mutex> lock(_server_mtx);
	auto minserver = _servers.begin()->second;
	//每个服务器连接的数量记录在Redis中，先从Redis中查询服务器连接的数量
	auto count_str = RedisMgr::GetInstance()->HGet(LOGIN_COUNT, minserver.name);
	if (count_str.empty()) {
		//如果为空，设置为最大值
		minserver.con_count = INT_MAX;
	}
	else {
		//记录服务器连接数量
		minserver.con_count = std::stoi(count_str);
	}
	for (auto& server : _servers) {
		if (server.second.name == minserver.name) {
			continue;
		}
		auto count_str = RedisMgr::GetInstance()->HGet(LOGIN_COUNT, server.second.name);
		if (count_str.empty()) {
			server.second.con_count = INT_MAX;
		}
		else {
			server.second.con_count = std::stoi(count_str);
		}
		//对比取出连接数量最少的服务器
		if (minserver.con_count > server.second.con_count) {
			minserver = server.second;
		}
	}
	return minserver;
}
