#pragma once
#include <string>
#include "const.h"
#include <iostream>
#include <boost/asio.hpp>

class LogicSystem;
class MsgNode
{
public:
	MsgNode(std::size_t maxLen);
	~MsgNode();

	void Clear();

public:
	std::size_t _curlen;
	std::size_t _totalLen;
	char* _data;
};

class RecvNode : public MsgNode 
{
	friend class LogicSystem;
public:
	RecvNode(std::size_t maxLen, std::size_t msgId);
private:
	std::size_t _msgId;
};
class SendNode : public MsgNode
{
	friend class LogicSystem;
public:
	SendNode(const char* data, std::size_t maxLen, std::size_t msgId);
private:
	std::size_t _msgId;
};

