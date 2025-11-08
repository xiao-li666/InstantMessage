#include <iostream>
#include <string>
#include "CServer.h"
#include "ConfigMgr.h"
#include "const.h"

int main()
{
	std::string gatePortStr = ConfigMgr::GetInstance()["GateServer"]["Port"];
	unsigned short gatePort = atoi(gatePortStr.c_str());
    try {
        net::io_context ioc{ 1 };
		boost::asio::signal_set signals(ioc, SIGINT, SIGTERM);
		signals.async_wait([&ioc](const boost::system::error_code& err, int signal_number) {
			if (err) {
				return;
			}
			ioc.stop();
			});
		std::make_shared<CServer>(ioc, gatePort)->Start();
		std::cout << "Server started at port " << gatePort << std::endl;
		ioc.run();
    }
    catch (std::exception& ec) {
		std::cerr << ec.what() << std::endl;
		return EXIT_FAILURE;
    }
}