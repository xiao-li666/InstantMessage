#include <json/json.h>
#include <json/value.h>
#include <json/reader.h>
#include "const.h"
#include "ConfigMgr.h"
#include "hiredis.h"
#include "RedisMgr.h"
#include "MysqlMgr.h"
#include "AsioIOServicePool.h"
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <boost/asio.hpp>
#include "StatusServerImpl.h"

void RunServer() {
    auto& conf = ConfigMgr::GetInstance();
    std::string serverAddress(conf["StatusServer"]["Host"] + ":" + conf["StatusServer"]["Port"]);
    StatusServerImpl service;
    
    grpc::ServerBuilder bulider;
    bulider.AddListeningPort(serverAddress, grpc::InsecureServerCredentials());
    bulider.RegisterService(&service);

    //开启grpc服务器
    std::unique_ptr<grpc::Server> server(bulider.BuildAndStart());
    std::cout << "server listening on" << serverAddress << std::endl;

    //创建boost::asio的io_context
    boost::asio::io_context io_context;
    //监听信号
    boost::asio::signal_set signals(io_context, SIGINT, SIGTERM);

    //设置异步等待信号
    signals.async_wait([&server](const boost::system::error_code& err, int signal_number) {
        if (!err) {
            std::cout << "shutting down server" << std::endl;
            server->Shutdown();//关闭服务器, 会等待所有正在处理的请求完成，然后清理资源
        }
        });

    //在单独的线程中开启io_context
    std::thread([&io_context]() {
        io_context.run();
        }).detach();

    //等待服务器关闭
    server->Wait();
    io_context.stop();
}

int main()
{
    try {
        RunServer();
    }
    catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return 0;
}

