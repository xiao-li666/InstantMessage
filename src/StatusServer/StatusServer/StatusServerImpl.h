#pragma once
#include <grpcpp/grpcpp.h>
#include "message.grpc.pb.h"
#include <mutex>
#include <unordered_map>
#include <boost/uuid/uuid.hpp>           // UUID 类型
#include <boost/uuid/uuid_generators.hpp> // UUID 生成器
#include <boost/uuid/uuid_io.hpp>        // UUID 的输入输出操作

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using message::GetChatServerReq;
using message::GetChatServerRsp;
using message::LoginReq;
using message::LoginRsp;
using message::StatusService;

struct ChatServer {
	std::string host;
	std::string port;
	std::string name;
	int con_count; //用来记录当前服务器的连接数量
};

class StatusServerImpl final : public StatusService::Service
{
public:
	StatusServerImpl();
	~StatusServerImpl();

	Status GetChatServer(ServerContext* context, const GetChatServerReq* request,
		GetChatServerRsp* reply) override;
	Status Login(ServerContext* context, const LoginReq* request,
		LoginRsp* reply) override;

private:
	void insertToken(int uid, std::string token);
	ChatServer getChatServer();
	std::unordered_map<std::string, ChatServer> _servers;
	std::mutex _server_mtx;
	std::unordered_map<int, std::string> _tokens;
	std::mutex _token_mtx;
};

