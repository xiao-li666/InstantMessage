#include "MsgNode.h"
#include "LogicSystem.h"
MsgNode::MsgNode(std::size_t maxLen) : _totalLen(maxLen),_curlen(0)
{
	_data = new char[_totalLen + 1]();
	_data[_totalLen] = '\0';
}

MsgNode::~MsgNode()
{
	std::cout << "MsgNode is distructed" << std::endl;
	delete[]_data;
}

void MsgNode::Clear()
{
	memset(_data, 0, _totalLen);
	_curlen = 0;
}

RecvNode::RecvNode(std::size_t maxLen, std::size_t msgId)
	:MsgNode(maxLen),_msgId(msgId)
{
}

SendNode::SendNode(const char* data, std::size_t maxLen, std::size_t msgId)
	:MsgNode(maxLen + HEAD_TOTAL_LEN),_msgId(msgId)
{
	std::size_t msgIdHost = boost::asio::detail::socket_ops::host_to_network_short(_msgId);
	memcpy(_data, &msgIdHost, HEAD_ID_LEN);
	std::size_t msgLenHost = boost::asio::detail::socket_ops::host_to_network_short(maxLen);
	memcpy(_data + HEAD_ID_LEN, &msgLenHost, HEAD_DATA_LEN);
	memcpy(_data + HEAD_TOTAL_LEN, data, maxLen);
}
