#pragma once
#include "const.h"
#include "Singleton.h"
#include "ConfigMgr.h"
#include <grpcpp/grpcpp.h>
#include "message.grpc.pb.h"
#include "message.pb.h"

using grpc::Channel;
using grpc::Status;
using grpc::ClientContext;

using message::GetChatServerReq;
using message::GetChatServerRsp;
using message::LoginReq;
using message::LoginRsp;
using message::StatusService;

class StatusConPool {
public:
	StatusConPool(size_t poolsize, std::string host, std::string port)
		:poolsize_(poolsize), host_(host), port_(port)
	{
		for (size_t i = 0; i < poolsize; i++) {
			std::shared_ptr<Channel> channel = grpc::CreateChannel(host + ":" + port, grpc::InsecureChannelCredentials());
			connections_.push(StatusService::NewStub(channel));
		}
	}
	~StatusConPool() {
		std::lock_guard<std::mutex> lock(_mutex);
		Close();
		while (!connections_.empty()) {
			connections_.pop();
		}
	}
	std::unique_ptr<StatusService::Stub> getConnection() {
		std::unique_lock<std::mutex> lock(_mutex);
		_cond.wait(lock, [this]() {
			if (_bStop) {
				return true;
			}
			return !connections_.empty();
			});
		if (_bStop) {
			return nullptr;
		}
		auto context = std::move(connections_.front());
		connections_.pop();
		return context;
	}
	void returnConnection(std::unique_ptr<StatusService::Stub> stub)
	{
		std::lock_guard<std::mutex> lock(_mutex);
		if (_bStop) {
			return;
		}
		connections_.push(std::move(stub));
		_cond.notify_one();
	}
	void Close() {
		_bStop = true;
		_cond.notify_all();
	}
private:
	std::queue<std::unique_ptr<StatusService::Stub>> connections_;
	std::mutex _mutex;
	std::condition_variable _cond;
	std::size_t poolsize_;
	std::string host_;
	std::string port_;
	std::atomic<bool> _bStop;
};

class StatusGrpcClient : public Singleton<StatusGrpcClient>
{
	friend class Singleton<StatusGrpcClient>;
public:
	~StatusGrpcClient();

	GetChatServerRsp GetChatServer(int32_t uid);
	LoginRsp Login(int uid, std::string token);
private:
	StatusGrpcClient();
	std::unique_ptr<StatusConPool> pool_;
};
