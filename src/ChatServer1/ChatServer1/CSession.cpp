#include "CSession.h"
#include "LogicSystem.h"

CSession::CSession(boost::asio::io_context& io_context, CServer* server)
	:_socket(io_context),_b_close(false),_server(server),_b_head_parse(false)
{
	//生成uuid
	// 创建UUID对象
	boost::uuids::uuid uuid = boost::uuids::random_generator()();
	// 将UUID转换为字符串
	_uuid = to_string(uuid);
	_recv_head_node = std::make_shared<MsgNode>(HEAD_TOTAL_LEN);
}

tcp::socket& CSession::GetSocket()
{
	return _socket;
}

std::string CSession::GetUuid()
{
	return _uuid;
}
void CSession::Start()
{
	//首先接收头部
	AsyncReadHead(HEAD_TOTAL_LEN);
}
void CSession::Close()
{
	std::lock_guard<std::mutex> lock(_session_mtx);
	_socket.close();
	_b_close = true;
}
void CSession::AsyncReadHead(std::size_t length)
{
	auto self = shared_from_this();
	asyncReadFull(length, [self, this,length](const boost::system::error_code& err, std::size_t bytes_transfered) {
		try{
			if (err) {
				std::cout << "handle read failed error is" << err.what() << std::endl;
				Close();
				_server->ClearSession(_uuid);
				return;
			}
			if (bytes_transfered < length) {
				std::cout << "read length not match, read [" << bytes_transfered << "], total [" << length << "]" << std::endl;
				Close();
				_server->ClearSession(_uuid);
				return;
			}
			//判断链接无效
			if (!_server->checkValid(_uuid)) {
				Close();
				return;
			}
			_recv_head_node->Clear();
			memcpy(_recv_head_node->_data, _data, bytes_transfered);
			std::size_t msgId = 0;
			memcpy(&msgId, _data, HEAD_ID_LEN);
			msgId = boost::asio::detail::socket_ops::network_to_host_short(msgId);
			std::cout << "msgid is " << msgId << std::endl;
			std::size_t msgLen = 0;
			memcpy(&msgLen, _data + HEAD_ID_LEN, HEAD_DATA_LEN);
			msgLen = boost::asio::detail::socket_ops::network_to_host_short(msgLen);
			std::cout << "msgLen is " << msgLen << std::endl;

			if (msgLen > MAX_LENGTH) {
				//长度非法
				std::cout << "msgLen is too length len = " << msgLen << std::endl;
				_server->ClearSession(_uuid);
				return;
			}
			//头部信息接收完成，创建消息体结点
			_recv_msg_node = std::make_shared<RecvNode>(msgLen, msgId);
			AsyncReadBody(msgLen);
		}
		catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	});
}

void CSession::AsyncReadBody(std::size_t totalLen)
{
	auto self = shared_from_this();
	asyncReadFull(totalLen, [self, this, totalLen](const boost::system::error_code& err, std::size_t bytes_transfered) {
		if (err) {
			std::cout << "handle read failed error is" << err.what() << std::endl;
			Close();
			_server->ClearSession(_uuid);
			return;
		}
		if (bytes_transfered < totalLen) {
			std::cout << "read length not match, read [" << bytes_transfered << "], total [" << totalLen << "]" << std::endl;
			Close();
			_server->ClearSession(_uuid);
			return;
		}
		//判断链接无效
		if (!_server->checkValid(_uuid)) {
			Close();
			return;
		}
		memcpy(_recv_msg_node->_data, _data, totalLen);
		_recv_msg_node->_curlen += bytes_transfered;
		std::cout << "receive data is " << _recv_msg_node->_data << std::endl;

		// 此处将消息投递到逻辑队列中
		LogicSystem::GetInstance()->PostMsgToQue(std::make_shared<LogicNode>(shared_from_this(), _recv_msg_node));
		//继续监听头部接受事件
		AsyncReadHead(HEAD_TOTAL_LEN);
	});
}

void CSession::asyncReadFull(std::size_t length, std::function<void(const boost::system::error_code& err, std::size_t bytes_transfered)> handler)
{
	memset(_data, 0, MAX_LENGTH);
	asyncReadLen(0, length, handler);
}

void CSession::asyncReadLen(std::size_t read_len, std::size_t total_len, 
	std::function<void(const boost::system::error_code& err, std::size_t bytes_transfered)> handler)
{
	auto self = shared_from_this();
	_socket.async_read_some(boost::asio::buffer(_data + read_len, total_len - read_len),
		[read_len, total_len, handler, self](const boost::system::error_code& ec, std::size_t  bytesTransfered) {
			if (ec) {
				// 出现错误，调用回调函数
				handler(ec, read_len + bytesTransfered);
				return;
			}

			if (read_len + bytesTransfered >= total_len) {
				//长度够了就调用回调函数
				handler(ec, read_len + bytesTransfered);
				return;
			}

			// 没有错误，且长度不足则继续读取
			self->asyncReadLen(read_len + bytesTransfered, total_len, handler);
		});
}

void CSession::Send(std::string msg, std::size_t msgid)
{
	std::lock_guard<std::mutex> lock(_sendMtx);
	auto sendQueSize = _sendQue.size();
	if (sendQueSize > MAX_SENDQUE) {
		std::cout << "session: " << _uuid << " send que fulled, size is " << MAX_SENDQUE << std::endl;
		return;
	}
	_sendQue.push(std::make_shared<SendNode>(msg.c_str(), msg.length(), msgid));
	if (sendQueSize > 0) {
		return;
	}
	auto& msgnode = _sendQue.front();
	boost::asio::async_write(_socket, boost::asio::buffer(msgnode->_data, msgnode->_totalLen),
		std::bind(&CSession::HandleWrite, this, std::placeholders::_1, shared_from_this()));
}

void CSession::Send(char* msg, std::size_t max_length, std::size_t msgid)
{
	std::lock_guard<std::mutex> lock(_sendMtx);
	auto sendQueSize = _sendQue.size();
	if (sendQueSize > MAX_SENDQUE) {
		std::cout << "session: " << _uuid << " send que fulled, size is " << MAX_SENDQUE << std::endl;
		return;
	}
	_sendQue.push(std::make_shared<SendNode>(msg, max_length, msgid));
	if (sendQueSize > 0) {
		return;
	}
	auto& msgnode = _sendQue.front();
	boost::asio::async_write(_socket, boost::asio::buffer(msgnode->_data, msgnode->_totalLen),
		std::bind(&CSession::HandleWrite, this, std::placeholders::_1, shared_from_this()));
}

void CSession::HandleWrite(const boost::system::error_code& error, std::shared_ptr<CSession> shared_self)
{
	//增加异常处理
	try {
		auto self = shared_from_this();
		if (!error) {
			std::lock_guard<std::mutex> lock(_sendMtx);
			//cout << "send data " << _send_que.front()->_data+HEAD_LENGTH << endl;
			_sendQue.pop();
			if (!_sendQue.empty()) {
				auto& msgnode = _sendQue.front();
				boost::asio::async_write(_socket, boost::asio::buffer(msgnode->_data, msgnode->_totalLen),
					std::bind(&CSession::HandleWrite, this, std::placeholders::_1, shared_self));
			}
		}
		else {
			std::cout << "handle write failed, error is " << error.what() << std::endl;
			Close();
			//DealExceptionSession();
		}
	}
	catch (std::exception& e) {
		std::cerr << "Exception code : " << e.what() << std::endl;
	}
}

LogicNode::LogicNode(std::shared_ptr<CSession> session, std::shared_ptr<RecvNode> recvnode)
	:_session(session), _recvnode(recvnode)
{
}
