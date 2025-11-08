#include "StatusServerImpl.h"
#include "ConfigMgr.h"


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
	ChatServer server;
	server.host = conf["ChatServer1"]["Host"];
	server.port = conf["ChatServer1"]["Port"];
	server.name = conf["ChatServer1"]["Name"];
	server.con_count = 0;
	_servers[server.name] = server;

	//server.host = conf["ChatServer2"]["Host"];
	//server.port = conf["ChatServer2"]["Port"];
	//server.name = conf["ChatServer2"]["Name"];
	//server.con_count = 0;
	//_servers[server.name] = server;
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
	std::lock_guard<std::mutex> lock(_token_mtx);
	auto iter = _tokens.find(uid);
	if (iter == _tokens.end()) {
		reply->set_error(ErrorCodes::UidInvalid);
		return Status::OK;
	}
	std::cout << "iter->second is " << iter->second << std::endl;
	if (iter->second != token) {
		reply->set_error(ErrorCodes::TokenInvalid);
		return Status::OK;
	}
	reply->set_error(ErrorCodes::Success);
	reply->set_uid(uid);
	reply->set_token(token);
	std::cout << "Login has send reply" << std::endl;
	return Status::OK;
}

void StatusServerImpl::insertToken(int uid, std::string token)
{
	std::lock_guard<std::mutex> lock(_token_mtx);
	_tokens[uid] = token;
}

ChatServer StatusServerImpl::getChatServer()
{
	std::lock_guard<std::mutex> lock(_server_mtx);
	auto minserver = _servers.begin()->second;
	for (auto& server : _servers) {
		if (server.second.con_count < minserver.con_count) {
			minserver = server.second;
		}
	}
	return minserver;
}
