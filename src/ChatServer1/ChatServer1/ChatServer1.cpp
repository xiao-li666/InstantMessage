
#include <iostream>
#include "CServer.h"
#include "const.h"
#include "ConfigMgr.h"

int main()
{
    try {
        boost::asio::io_context io_context;
        ConfigMgr &conf = ConfigMgr::GetInstance();
        auto pool_ = AsioIOServicePool::GetInstance();
        boost::asio::signal_set signals(io_context, SIGINT, SIGTERM);
        signals.async_wait([&io_context, &pool_](auto, auto) {
            io_context.stop();
            pool_->Stop();
            });
        auto port = conf["ChatServer1"]["Port"];
        CServer server(io_context, atoi(port.c_str()));
        io_context.run();
    }
    catch (std::exception& ec) {
        std::cout << ec.what() << std::endl;
    }
}
