#include "StatusGrpcClient.h"

StatusConPool::StatusConPool(size_t poolsize, std::string host, std::string port)
	:_poolsize(poolsize), _host(host), _port(port)
{
	for (size_t i = 0; i < poolsize; i++) {
		//´´½¨Channel
		std::shared_ptr<Channel> channel = grpc::CreateChannel(host + ":" + port, grpc::InsecureChannelCredentials());
		_connections.push(StatusService::NewStub(channel));
	}

}

StatusConPool::~StatusConPool()
{
	std::lock_guard<std::mutex> lock(_mutex);
	Close();
	while (!_connections.empty()) {
		_connections.pop();
	}
}

std::unique_ptr<StatusService::Stub> StatusConPool::getConnection()
{
	std::unique_lock<std::mutex> lock(_mutex);
	_cond.wait(lock, [this] {
		if (_b_stop) {
			return true;
		}
		return !_connections.empty();
		});
	if (_b_stop) {
		return nullptr;
	}
	auto conn = std::move(_connections.front());
	_connections.pop();
	return conn;
}

void StatusConPool::returnConnection(std::unique_ptr<StatusService::Stub> conn)
{
	std::unique_lock<std::mutex> lock(_mutex);
	if (_b_stop) {
		return;
	}
	_connections.push(std::move(conn));
	_cond.notify_one();
}

void StatusConPool::Close()
{
	_b_stop = true;
	_cond.notify_all();
}

StatusGrpcClient::~StatusGrpcClient()
{
}

StatusGrpcClient::StatusGrpcClient()
{
	auto& gCfgMgr = ConfigMgr::GetInstance();
	std::string host = gCfgMgr["StatusServer"]["Host"];
	std::string port = gCfgMgr["StatusServer"]["Port"];
	_pool.reset(new StatusConPool(5, host, port));
}

GetChatServerRsp StatusGrpcClient::GetChatServer(int uid)
{
	ClientContext context;
	GetChatServerRsp reply;
	GetChatServerReq request;
	request.set_uid(uid);
	auto stub = _pool->getConnection();
	Status status = stub->GetChatServer(&context, request, &reply);
	Defer defer([&stub, this]() {
		_pool->returnConnection(std::move(stub));
		});
	if (status.ok()) {
		return reply;
	}
	else {
		reply.set_error(ErrorCodes::RPCFailed);
		return reply;
	}
}

LoginRsp StatusGrpcClient::Login(int uid, std::string token)
{
	ClientContext context;
	LoginRsp reply;
	LoginReq request;
	request.set_uid(uid);
	request.set_token(token);

	auto stub = _pool->getConnection();
	Status status = stub->Login(&context, request, &reply);
	Defer defer([&stub, this]() {
		_pool->returnConnection(std::move(stub));
		});
	if (status.ok()) {
		return reply;
	}
	else {
		reply.set_error(ErrorCodes::RPCFailed);
		return reply;
	}
}
