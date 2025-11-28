#pragma once
#include "const.h"
#include "Singleton.h"
#include "ConfigMgr.h"
#include "message.grpc.pb.h"
#include "message.pb.h"
#include <grpcpp/grpcpp.h>
#include <queue>
#include <condition_variable>
using grpc::Channel;
using grpc::Status;
using grpc::ClientContext;

using message::GetChatServerReq;
using message::GetChatServerRsp;
using message::LoginRsp;
using message::LoginReq;
using message::StatusService;

class StatusConPool 
{
public:
	StatusConPool(size_t poolsize, std::string host, std::string port);
	~StatusConPool();
	std::unique_ptr<StatusService::Stub> getConnection();
	void returnConnection(std::unique_ptr<StatusService::Stub> conn);
	void Close();
private:
	std::atomic<bool> _b_stop;
	std::queue<std::unique_ptr<StatusService::Stub>> _connections;
	std::mutex _mutex;
	std::condition_variable _cond;
	std::string _host;
	std::string _port;
	size_t _poolsize;
};

class StatusGrpcClient : public Singleton<StatusGrpcClient>
{
public:
	friend class Singleton<StatusGrpcClient>;
	~StatusGrpcClient();
	GetChatServerRsp GetChatServer(int uid);
	LoginRsp Login(int uid, std::string token);
private:
	StatusGrpcClient();

	std::unique_ptr<StatusConPool> _pool;
};

