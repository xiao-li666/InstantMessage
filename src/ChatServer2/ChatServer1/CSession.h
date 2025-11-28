#pragma once
#include "CServer.h"
#include "const.h"
#include <boost/uuid/uuid.hpp>           // UUID 类型
#include <boost/uuid/uuid_generators.hpp> // UUID 生成器
#include <boost/uuid/uuid_io.hpp>        // UUID 的输入输出操作
class CSession : public std::enable_shared_from_this<CSession>
{
public:
	CSession(boost::asio::io_context& io_context, CServer* server);

	tcp::socket& GetSocket();

	void Start();
	void Close();
	std::string GetSessionuid();
	int GetUseruid();
	void SetUserUid(int uid);
	void AsyncReadHead(std::size_t length);
	void AsyncReadBody(std::size_t totalLen);
	void asyncReadFull(std::size_t length, std::function<void(const boost::system::error_code& err, std::size_t bytes_transfered)>);
	void asyncReadLen(std::size_t read_len, std::size_t total_len, std::function<void(const boost::system::error_code& err, std::size_t bytes_transfered)>);
	void Send(std::string msg, std::size_t msgid);
	void Send(char* msg, std::size_t max_length, std::size_t msgid);
	void HandleWrite(const boost::system::error_code& error, std::shared_ptr<CSession> shared_self);
private:

	tcp::socket _socket;
	std::string _sessionuid;
	int _useruid;
	CServer* _server;
	char _data[MAX_LENGTH];
	std::mutex _session_mtx;
	bool _b_close;
	//收到的消息结构
	std::shared_ptr<RecvNode> _recv_msg_node;
	bool _b_head_parse;
	//收到的头部结构
	std::shared_ptr<MsgNode> _recv_head_node;

	//发送队列
	std::queue<std::shared_ptr<SendNode>> _sendQue;
	std::mutex _sendMtx;
};

class LogicNode {
	friend class LogicSystem;
public:
	LogicNode(std::shared_ptr<CSession>, std::shared_ptr<RecvNode>);
private:
	std::shared_ptr<CSession> _session;
	std::shared_ptr<RecvNode> _recvnode;
};

