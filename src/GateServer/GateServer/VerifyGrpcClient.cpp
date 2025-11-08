#include "VerifyGrpcClient.h"
#include "ConfigMgr.h"
VerifyGrpcClient::VerifyGrpcClient()
{
	auto& gConfMgr = ConfigMgr::GetInstance();
	std::string host = gConfMgr["VarifyServer"]["Host"];
	std::string port = gConfMgr["VarifyServer"]["Port"];
	_pool.reset(new RPConPool(5,host,port));
}
VerifyGrpcClient::~VerifyGrpcClient()
{
}

GetVarifyRsp VerifyGrpcClient::GetVerifyCode(std::string email)
{
    ClientContext context;
    GetVarifyRsp replay;
	GetVarifyReq request;
	request.set_email(email);
	auto stub = _pool->getConnection();
	Status status = stub->GetVarifyCode(&context, request, &replay);
	if (status.ok()) {
		_pool->returnConnection(std::move(stub));
		return replay;
	}
	else {
		replay.set_error(ErrorCodes::RPCFailed);
		_pool->returnConnection(std::move(stub));
		return replay;
	}
}

RPConPool::RPConPool(std::size_t poolsize, std::string host, std::string port)
	:_poolSize(poolsize),_host(host),_port(port),_bStop(false)
{
	for (std::size_t i = 0; i < poolsize; i++) {
		std::shared_ptr<Channel> channel = grpc::CreateChannel(host+":"+port, grpc::InsecureChannelCredentials());
		_connections.push(VarifyService::NewStub(channel));
	}
}

RPConPool::~RPConPool()
{
	std::lock_guard<std::mutex> lock(_mutex);
	Close();
	while (!_connections.empty()) {
		_connections.pop();
	}
}

void RPConPool::Close()
{
	_bStop = true;
	_cond.notify_all();
}

std::unique_ptr<VarifyService::Stub> RPConPool::getConnection()
{
	std::unique_lock<std::mutex> lock(_mutex);
	_cond.wait(lock, [this]() {
		if (_bStop) {
			return true;
		}
		return !_connections.empty();
		});
	if (_bStop) {
		return nullptr;
	}
	auto context = std::move(_connections.front());
	_connections.pop();
	return context;
}

void RPConPool::returnConnection(std::unique_ptr<VarifyService::Stub> stub)
{
	std::lock_guard<std::mutex> lock(_mutex);
	if (_bStop) {
		return;
	}
	_connections.push(std::move(stub));
	_cond.notify_one();
}
