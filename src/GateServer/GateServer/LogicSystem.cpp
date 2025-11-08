#include "LogicSystem.h"
#include "HttpConnection.h"
#include "VerifyGrpcClient.h"
#include "MysqlMgr.h"
#include "StatusGrpcClient.h"

LogicSystem::LogicSystem() 
{
	RegGet("/getTest", [](std::shared_ptr<HttpConnection> conn) {
		//处理GET请求的逻辑
		beast::ostream(conn->response_.body()) << "This is a test response for /getTest";
		for (auto& param : conn->getParams_) {
			beast::ostream(conn->response_.body()) << "\nParam: " << param.first << " = " << param.second;
		}
		});
	RegPost("/getVarifycode", [](std::shared_ptr<HttpConnection> conn) {
		//处理POST请求的逻辑
		auto bodyStr = boost::beast::buffers_to_string(conn->request_.body().data());
		std::cout << "received body is " << bodyStr << std::endl;
		conn->response_.set(http::field::content_type, "text/json");
		Json::Value root;
		Json::Reader reader;
		Json::Value srcRoot;
		bool parseSuccess = reader.parse(bodyStr, srcRoot);
		if (!parseSuccess) {
			std::cout << "failed to parse JSON data!" << std::endl;
			root["error"] = ErrorCodes::Error_Json;
			std::string jsonstr = root.toStyledString();
			beast::ostream(conn->response_.body()) << jsonstr;
			return true;
		}
		if (!srcRoot.isMember("email"))
		{
			std::cout << "failed to parse JSON data!" << std::endl;
			root["error"] = ErrorCodes::Error_Json;
			std::string jsonstr = root.toStyledString();
			beast::ostream(conn->response_.body()) << jsonstr;
			return true;
		}

		auto email = srcRoot["email"].asString();
		//调用gRPC客户端获取验证码
		GetVarifyRsp rsp = VerifyGrpcClient::GetInstance()->GetVerifyCode(email);

		std::cout << "email is " << email << std::endl;
		root["error"] = rsp.error();
		root["email"] = srcRoot["email"];
		std::string jsonStr = root.toStyledString();
		beast::ostream(conn->response_.body()) << jsonStr;
		return true;
		});
	RegPost("/userRegister", [](std::shared_ptr<HttpConnection> conn) {
		auto bodyStr = boost::beast::buffers_to_string(conn->request_.body().data());
		std::cout << "received body is " << bodyStr << std::endl;
		conn->response_.set(boost::beast::http::field::content_type, "text/json");
		Json::Value root;
		Json::Reader reader;
		Json::Value srcRoot;

		bool praseSuccess = reader.parse(bodyStr, srcRoot);
		if (!praseSuccess) {
			std::cout << "JSON parse is failed!" << std::endl;
			root["error"] = ErrorCodes::Error_Json;
			std::string res = root.toStyledString();
			beast::ostream(conn->response_.body()) << res;
			return true;
		}
		//在redis中查找验证码
		std::string varifyCode;
		bool flag = RedisMgr::GetInstance()->Get(KEYPRE + srcRoot["email"].asString(), varifyCode);
		if (!flag) {
			//验证超时
			std::cout << "search from redis is null to" << srcRoot["email"].asString() << std::endl;
			root["error"] = ErrorCodes::VarifyExpire;
			std::string resString = root.toStyledString();
			beast::ostream(conn->response_.body()) << resString;
			return true;
		}
		if (varifyCode != srcRoot["varify"].asString()) {
			//验证码错误
			std::cout << "varify code is error!" << std::endl;
			root["error"] = ErrorCodes::VarifyCodeError;
			std::string resString = root.toStyledString();
			beast::ostream(conn->response_.body()) << resString;
			return true;
		}

		//查找数据库判断用户是否存在，不存在加进去，存在返回错误
		std::string name = srcRoot["user"].asString();
		std::string email = srcRoot["email"].asString();
		std::string passwd = srcRoot["passwd"].asString();
		int uid = MysqlMgr::GetInstance()->RegUser(name,email , passwd);
		if (uid == 0 || uid == -1) {
			std::cout << "user or email exist" << std::endl;
			root["error"] = ErrorCodes::UserExits;
			std::string resString = root.toStyledString();
			beast::ostream(conn->response_.body()) << resString;
			return true;
		}

		root["error"] = ErrorCodes::Success;
		root["email"] = srcRoot["email"].asString();
		root["uid"] = uid;
		root["user"] = srcRoot["user"].asString();
		root["passwd"] = srcRoot["passwd"].asString();
		root["confirm"] = srcRoot["confirm"].asString();
		root["varify"] = srcRoot["varify"].asString();
		std::string resString = root.toStyledString();
		beast::ostream(conn->response_.body()) << resString;
		return true;
		});
	//重置密码
	RegPost("/resetPass", [](std::shared_ptr<HttpConnection> conn) {
		std::string bodyStr = boost::beast::buffers_to_string(conn->request_.body().data());
		std::cout << "request body is " << bodyStr << std::endl;
		conn->response_.set(boost::beast::http::field::content_type, "text/json");
		Json::Value root;
		Json::Reader reader;
		Json::Value srcRoot;
		bool jsonRes = reader.parse(bodyStr, srcRoot);
		if (!jsonRes) {
			std::cout << "JSON parse is failed!" << std::endl;
			root["error"] = ErrorCodes::Error_Json;
			std::string res = root.toStyledString();
			beast::ostream(conn->response_.body()) << res;
			return true;
		}
		//在redis中查找验证码
		std::string varifyCode;
		bool flag = RedisMgr::GetInstance()->Get(KEYPRE + srcRoot["email"].asString(), varifyCode);
		if (!flag) {
			//验证超时
			std::cout << "search from redis is null to" << srcRoot["email"].asString() << std::endl;
			root["error"] = ErrorCodes::VarifyExpire;
			std::string resString = root.toStyledString();
			beast::ostream(conn->response_.body()) << resString;
			return true;
		}
		if (varifyCode != srcRoot["varify"].asString()) {
			//验证码错误
			std::cout << "varify code is error!" << std::endl;
			root["error"] = ErrorCodes::VarifyCodeError;
			std::string resString = root.toStyledString();
			beast::ostream(conn->response_.body()) << resString;
			return true;
		}
		//在数据库中查找用户是否存在，如果存在修改密码，不存在返回用户不存在
		bool checkSuccess = MysqlMgr::GetInstance()->checkEmail(srcRoot["user"].asString(),srcRoot["email"].asString());
		if (!checkSuccess) {
			//用户不存在
			root["error"] = ErrorCodes::UserNoExits;
			std::string resString = root.toStyledString();
			beast::ostream(conn->response_.body()) << resString;
			return true;
		}
		bool updateSuccess = MysqlMgr::GetInstance()->updatePwd(srcRoot["email"].asString(), srcRoot["password"].asString());
		if (!updateSuccess) {
			//更新失败
			root["error"] = ErrorCodes::PasswdUpFailed;
			std::string resString = root.toStyledString();
			beast::ostream(conn->response_.body()) << resString;
			return true;
		}
		std::cout << "password update success!" << std::endl;
		root["error"] = ErrorCodes::Success;
		root["email"] = srcRoot["email"].asString();
		root["user"] = srcRoot["user"].asString();
		root["password"] = srcRoot["password"].asString();
		std::string resString = root.toStyledString();
		beast::ostream(conn->response_.body()) << resString;
		return true;
		});
	RegPost("/login", [this](std::shared_ptr<HttpConnection> connect) {
		auto bodyStr = boost::beast::buffers_to_string(connect->request_.body().data());
		std::cout << "recv login requst is " << bodyStr << std::endl;
		Json::Value srcRoot;
		Json::Value root;
		Json::Reader reader;
		bool praseSuccess = reader.parse(bodyStr, srcRoot);
		if (!praseSuccess) {
			std::cout << "JSON prase failed!" << std::endl;
			root["error"] = ErrorCodes::Error_Json;
			std::string res = root.toStyledString();
			beast::ostream(connect->response_.body()) << res;
			return true;
		}
		auto email = srcRoot["email"].asString();
		auto pwd = srcRoot["pwd"].asString();

		//查询email的pwd，若能查到且相等返回登录成功，若没查到返回用户尚未注册，若查到密码不对返回密码错误
		UserInfo userInfo;
		bool selectSuccess = MysqlMgr::GetInstance()->selectPwd(email, userInfo);
		if (!selectSuccess) {
			std::cout << "user not exits" << std::endl;
			root["error"] = ErrorCodes::UserNoExits;
			std::string res = root.toStyledString();
			beast::ostream(connect->response_.body()) << res;
			return true;
		}
		if (pwd != userInfo.pwd) {
			//密码错误
			root["error"] = ErrorCodes::PassWdErr;
			std::string res = root.toStyledString();
			beast::ostream(connect->response_.body()) << res;
			return true;
		}
		//查询StatusServer找到合适的连接
		auto reply = StatusGrpcClient::GetInstance()->GetChatServer(userInfo.uid);
		if (reply.error()) {
			std::cout << " grpc get chat server failed, error is " << reply.error() << std::endl;
			root["error"] = ErrorCodes::RPCFailed;
			std::string jsonstr = root.toStyledString();
			beast::ostream(connect->response_.body()) << jsonstr;
			return true;
		}

		std::cout << "succeed to load userinfo uid is " << userInfo.uid << std::endl;
		root["error"] = ErrorCodes::Success;
		root["email"] = email;
		root["uid"] = userInfo.uid;
		root["token"] = reply.token();
		root["host"] = reply.host();
		root["port"] = reply.port();
		std::string jsonstr = root.toStyledString();
		beast::ostream(connect->response_.body()) << jsonstr;
		return true;

		});
}

LogicSystem::~LogicSystem()
{
}

bool LogicSystem::HandleGet(std::string path, std::shared_ptr<HttpConnection> conn)
{
	if (_getHandlers.find(path) == _getHandlers.end()) {
		return false;
	}
	_getHandlers[path](conn);
	return true;
}
void LogicSystem::RegGet(std::string url, HttpHandlerFunction handler)
{
	_getHandlers[url] = handler;
}

bool LogicSystem::HandlePost(std::string path, std::shared_ptr<HttpConnection> conn)
{
	if (_postHandlers.find(path) == _postHandlers.end()) {
		return false;
	}
	_postHandlers[path](conn);
	return true;
}

void LogicSystem::RegPost(std::string url, HttpHandlerFunction handler)
{
	_postHandlers[url] = handler;
}
