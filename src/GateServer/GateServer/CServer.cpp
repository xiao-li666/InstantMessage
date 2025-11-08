#include "CServer.h"
#include "HttpConnection.h"
#include "AsioIOServicePool.h"

CServer::CServer(boost::asio::io_context& ioc, unsigned short& port) : ioc_(ioc),
acceptor_(ioc, tcp::endpoint(tcp::v4(), port))
{

}

CServer::~CServer()
{
}

void CServer::Start()
{
	//获取shared_ptr实例
	auto self = shared_from_this();
	auto& ioContext = AsioIOServicePool::GetInstance()->GetIOService();
	std::shared_ptr<HttpConnection> newConn = std::make_shared<HttpConnection>(ioContext);
	//异步接受连接
	acceptor_.async_accept(newConn->GetSocket(), [self,newConn](boost::system::error_code ec)
	{
			try {

				if (!ec) {
					//连接成功，处理连接
					//创建HTTP连接对象并启动处理
					newConn->Start();
					self->Start();
				}
				else {
					//处理接受连接错误
					self->Start(); //继续接受下一个连接
					return;
				}

			}
			catch (std::exception& e) {
				//处理异常
				std::cerr << e.what() << std::endl;
			}
	});
}
