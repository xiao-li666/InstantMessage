
#include <iostream>
#include "CServer.h"
#include "const.h"
#include "ConfigMgr.h"
#include "RedisMgr.h"
#include "ChatServiceImpl.h"

int main()
{
	auto& conf = ConfigMgr::GetInstance();
	auto serverName = conf["SelfServer"]["Name"];
    try {
        auto pool_ = AsioIOServicePool::GetInstance();
		RedisMgr::GetInstance()->HSet(LOGIN_COUNT, serverName, "0");

		//启动ChatGrpc服务
		std::string server_address(conf["SelfServer"]["Host"] + ":" + conf["SelfServer"]["RPCPort"]);
		ChatServiceImpl chatService;
        grpc::ServerBuilder builder;
		builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
		builder.RegisterService(&chatService);
		//启动服务器
		std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
		std::cout << "Chat gRPC Server listening on " << server_address << std::endl;

		//单独线程运行grpc服务
        std::thread grpc_thread([&server]() {
            server->Wait();
            });

        boost::asio::io_context io_context;
        boost::asio::signal_set signals(io_context, SIGINT, SIGTERM);
        signals.async_wait([&io_context, &pool_,&server](auto, auto) {
            io_context.stop();
            pool_->Stop();
			server->Shutdown();
            });
        auto port = conf["SelfServer"]["Port"];
        CServer cserver(io_context, atoi(port.c_str()));
        io_context.run();

        RedisMgr::GetInstance()->HDel(LOGIN_COUNT, serverName);
        RedisMgr::GetInstance()->Close();
		grpc_thread.join();
    }
    catch (std::exception& ec) {
        std::cout << ec.what() << std::endl;
    }
}
