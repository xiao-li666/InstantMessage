#pragma once
#include "AsioIOServicePool.h"
class CSession;
class CServer
{
public:
	CServer(boost::asio::io_context &io_context, short port);
	void StartAccept();
	void HandleAccept(std::shared_ptr<CSession> newSession, const boost::system::error_code &err);
	void ClearSession(std::string sessionId);
	bool checkValid(std::string uid);
	//根据用户获取session
	std::shared_ptr<CSession> GetSession(std::string uuid);
private:

	boost::asio::io_context &_io_context;
	short _port;
	boost::asio::ip::tcp::acceptor _acceptor;
	std::map<std::string, std::shared_ptr<CSession>> _sessions;
	std::mutex _mutex;
};

