#include "ChatGrpcClient.h"


ChatConPool::ChatConPool(size_t poolsize, std::string host, std::string port)
	:_poolsize(poolsize), _host(host), _port(port),_b_stop(false)
{
	for (int i = 0; i < poolsize; i++) {
		//创建Channel
		std::shared_ptr<Channel> channel = grpc::CreateChannel(host + ":" + port, grpc::InsecureChannelCredentials());
		_connections.push(ChatService::NewStub(channel));
	}
}

ChatConPool::~ChatConPool()
{
	std::lock_guard<std::mutex> lock(_mutex);
	Close();
	while (!_connections.empty()) {
		_connections.pop();
	}
}

std::unique_ptr<ChatService::Stub> ChatConPool::getConnection()
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

void ChatConPool::returnConnection(std::unique_ptr<ChatService::Stub> conn)
{
	std::unique_lock<std::mutex> lock(_mutex);
	if (_b_stop) {
		return;
	}
	_connections.push(std::move(conn));
	_cond.notify_one();
}

void ChatConPool::Close()
{
	_b_stop = true;
	_cond.notify_all();
}

ChatGrpcClient::~ChatGrpcClient()
{
}

ChatGrpcClient::ChatGrpcClient()
{
	auto& config = ConfigMgr::GetInstance();
	auto server_list = config["PeerChatServer"]["Servers"];

	std::vector<std::string> words;

	std::stringstream ss(server_list);
	std::string word;

	while (std::getline(ss, word, ';')) {
		words.push_back(word);
	}

	//对应的服务器进行连接池的创建
	for (auto& word : words)
	{
		if (config[word]["Name"].empty()) {
			continue;
		}
		_pools[config[word]["Name"]] = std::make_unique<ChatConPool>(
			5,
			config[word]["Host"],
			config[word]["Port"]);
	}
}

AddFriendRsp ChatGrpcClient::NotifyAddFriend(std::string server_ip, const AddFriendReq& req)
{
	return AddFriendRsp();
}

AuthFriendRsp ChatGrpcClient::NotifyAuthFriend(std::string server_ip, const AuthFriendReq& req)
{
	return AuthFriendRsp();
}

bool ChatGrpcClient::GetBaseInfo(std::string base_key, int uid, std::shared_ptr<UserInfo>& userinfo)
{
	return false;
}

TextChatMsgRsp ChatGrpcClient::NotifyTextChatMsg(std::string server_ip, const TextChatMsgReq& req, const Json::Value& rtvalue)
{
	return TextChatMsgRsp();
}
