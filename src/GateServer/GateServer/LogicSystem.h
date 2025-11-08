#pragma once
#include "const.h"

class HttpConnection;
typedef std::function<void(std::shared_ptr<HttpConnection>)> HttpHandlerFunction;

class LogicSystem : public Singleton<LogicSystem>
{
public:
	friend class Singleton<LogicSystem>;
	~LogicSystem();

	bool HandleGet(std::string, std::shared_ptr<HttpConnection>);
	void RegGet(std::string, HttpHandlerFunction handler);
	bool HandlePost(std::string, std::shared_ptr<HttpConnection>);
	void RegPost(std::string, HttpHandlerFunction handler);


private:
	LogicSystem();

	std::map<std::string, HttpHandlerFunction> _postHandlers;
	std::map<std::string, HttpHandlerFunction> _getHandlers;
};

