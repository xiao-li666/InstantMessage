#pragma once
#include "const.h"

class CServer : public std::enable_shared_from_this<CServer>
{
public:
	CServer(boost::asio::io_context&ioc,unsigned short &port);
	~CServer();

	void Start();

private:
	tcp::acceptor acceptor_;
	net::io_context& ioc_;
};

