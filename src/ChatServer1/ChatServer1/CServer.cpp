#include "CServer.h"
#include "CSession.h"

CServer::CServer(boost::asio::io_context& io_context, short port)
	:_io_context(io_context), _port(port), _acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
{
	std::cout << "Server start success, listen on port : " << _port << std::endl;
	StartAccept();
}

void CServer::StartAccept()
{
	boost::asio::io_context& io_context = AsioIOServicePool::GetInstance()->GetIOService();
	std::shared_ptr<CSession> newSession = std::make_shared<CSession>(io_context, this);
	_acceptor.async_accept(newSession->GetSocket(), std::bind(&CServer::HandleAccept, this, newSession, std::placeholders::_1));
}

void CServer::HandleAccept(std::shared_ptr<CSession> newSession, const boost::system::error_code& err)
{
	if (!err) {
		newSession->Start();
		std::lock_guard<std::mutex> lock(_mutex);
		_sessions.insert({ newSession->GetUuid(), newSession });
		std::cout << "server seccess accept" << std::endl;
	}
	else {
		std::cout << "server failed accept" << std::endl;
	}
	StartAccept();
}

void CServer::ClearSession(std::string sessionId)
{
	std::lock_guard<std::mutex> lock(_mutex);
	if (_sessions.find(sessionId) != _sessions.end()) {

	}
	_sessions.erase(sessionId);
}

bool CServer::checkValid(std::string uid)
{
	std::lock_guard<std::mutex> lock(_mutex);
	auto it = _sessions.find(uid);
	if (it != _sessions.end()) {
		return true;
	}
	return false;
}

std::shared_ptr<CSession> CServer::GetSession(std::string uuid)
{
	std::lock_guard<std::mutex> lock(_mutex);
	if (_sessions.find(uuid) != _sessions.end()) {
		return _sessions[uuid];
	}
	else {
		return nullptr;
	}
}

