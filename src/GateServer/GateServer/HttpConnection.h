#pragma once
#include "const.h"

class HttpConnection : public std::enable_shared_from_this<HttpConnection>
{
public:
	friend class LogicSystem;
	HttpConnection(net::io_context &ioc);
	void Start();
	tcp::socket& GetSocket();

private:
	void CheackDeadline();
	void WriteResponse();
	void HandleRequest();
	void PreParseGetParam();

	tcp::socket socket_;
	beast::flat_buffer buffer_{8192};//缓冲区,用于存储读取的数据
	http::request<http::dynamic_body> request_;//HTTP请求对象
	http::response<http::dynamic_body> response_;//HTTP响应对象
	net::steady_timer deadline_{ socket_.get_executor(), std::chrono::seconds(60) };//定时器,用于连接超时检测
	std::unordered_map<std::string, std::string> getParams_;//存储GET请求参数
	std::string getUrl_;
};

