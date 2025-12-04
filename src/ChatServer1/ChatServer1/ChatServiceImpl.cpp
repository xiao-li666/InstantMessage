#include "ChatServiceImpl.h"
#include "const.h"
#include "UserMgr.h"
#include "CSession.h"
#include "MysqlMgr.h"

Status ChatServiceImpl::NotifyAddFriend(ServerContext* context, const AddFriendReq* request, AddFriendRsp* response)
{
	//查找用户是否在本服务器上在线
	auto uid = request->touid();
	auto session = UserMgr::GetInstance()->GetUserSession(uid);
	Defer defer([response, request]() {
		response->set_error(ErrorCodes::Success);
		response->set_applyuid(request->applyuid());
		response->set_touid(request->touid());
		});
	if (session == nullptr) {
		//如果用户不在线，直接返回成功
		return Status::OK;
	}
	//如果用户在线，发送好友申请通知
	Json::Value notifyValue;
	notifyValue["error"] = ErrorCodes::Success;
	notifyValue["applyuid"] = request->applyuid();
	notifyValue["name"] = request->name();
	notifyValue["desc"] = request->desc();
	notifyValue["icon"] = request->icon();
	notifyValue["sex"] = request->sex();
	notifyValue["nick"] = request->nick();
	std::string notifyStr = notifyValue.toStyledString();

	session->Send(notifyStr, ID_NOTIFY_ADD_FRIEND_REQ);
	std::cout << "ChatGrpcServer::NotifyAddFriend rpc success send ID_NOTIFY_ADD_FRIEND_REQ" << std::endl;

	return Status::OK;
}

Status ChatServiceImpl::NotifyAuthFriend(ServerContext* context, const AuthFriendReq* request, AuthFriendRsp* response)
{
	auto uid = request->touid();
	auto session = UserMgr::GetInstance()->GetUserSession(uid);
	response->set_error(ErrorCodes::Success);
	Defer defer([&response, &request]() {
		response->set_fromuid(request->fromuid());
		response->set_touid(request->touid());
		});
	if (session == nullptr) {
		//如果用户不在线，直接返回成功
		return Status::OK;
	}
	//如果用户在线，发送好友申请通过通知
	//查询自己的信息
	std::string base_key = USER_BASE_INFO + std::to_string(request->fromuid());
	auto selfUserInfo = std::make_shared<UserInfo>();
	bool b_info = GetBaseInfo(base_key, request->fromuid(), selfUserInfo);
	if (!b_info) {
		response->set_error(ErrorCodes::UserNoExits);
		return Status::OK;
	}
	Json::Value notifyValue;
	notifyValue["error"] = ErrorCodes::Success;
	notifyValue["fromuid"] = request->fromuid();
	notifyValue["name"] = selfUserInfo->name;
	notifyValue["nick"] = selfUserInfo->nick;
	notifyValue["icon"] = selfUserInfo->icon;
	notifyValue["sex"] = selfUserInfo->sex;

	std::string notifyStr = notifyValue.toStyledString();
	session->Send(notifyStr, ID_NOTIFY_AUTH_FRIEND_REQ);
	std::cout << "ChatGrpcServer::NotifyAuthFriend rpc success send ID_NOTIFY_AUTH_FRIEND_REQ" << std::endl;
    return Status::OK;
}

Status ChatServiceImpl::NotifyTextChatMsg(ServerContext* context, const TextChatMsgReq* request, TextChatMsgRsp* response)
{
	auto uid = request->touid();
	auto session = UserMgr::GetInstance()->GetUserSession(uid);
	response->set_error(ErrorCodes::Success);
	if (session == nullptr) {
		//如果用户不在线，直接返回成功
		return Status::OK;
	}
	Json::Value rtvalue;
	rtvalue["error"] = ErrorCodes::Success;
	rtvalue["fromuid"] = request->fromuid();
	rtvalue["touid"] = request->touid();
	Json::Value text_array;
	for (const auto& text_msg : request->textmsgs()) {
		Json::Value text_ele;
		text_ele["msgid"] = text_msg.msgid();
		text_ele["content"] = text_msg.msgcontent();
		text_array.append(text_ele);
	}
	rtvalue["text_array"] = text_array;
	std::string notifyStr = rtvalue.toStyledString();
	session->Send(notifyStr, ID_NOTIFY_TEXT_CHAT_MSG_REQ);

    return Status::OK;
}

bool ChatServiceImpl::GetBaseInfo(std::string base_key, int uid, std::shared_ptr<UserInfo>& userinfo)
{
	//先查找redis,redis中没有查到，再查mysql，查到后存入redis
	std::string infoStr = "";
	if (RedisMgr::GetInstance()->Get(base_key, infoStr)) {
		//redis中查询到用户的登录信息
		Json::Reader reader;
		Json::Value root;
		if (!reader.parse(infoStr, root)) {
			return false;
		}
		userinfo->uid = root["uid"].asInt();
		userinfo->name = root["name"].asString();
		userinfo->pwd = root["pwd"].asString();
		userinfo->email = root["email"].asString();
		userinfo->nick = root["nick"].asString();
		userinfo->desc = root["desc"].asString();
		userinfo->sex = root["sex"].asInt();
		userinfo->icon = root["icon"].asString();
	}
	else {
		//redis中没有查询到用户的登录信息，从mysql中查询
		std::shared_ptr<UserInfo> user_info = nullptr;
		user_info = MysqlMgr::GetInstance()->GetUser(uid);
		if (user_info == nullptr) {
			return false;
		}
		userinfo = user_info;
		//将用户的登录信息存入redis中
		Json::Value root;
		root["uid"] = userinfo->uid;
		root["name"] = userinfo->name;
		root["pwd"] = userinfo->pwd;
		root["email"] = userinfo->email;
		root["nick"] = userinfo->nick;
		root["desc"] = userinfo->desc;
		root["sex"] = userinfo->sex;
		root["icon"] = userinfo->icon;
		RedisMgr::GetInstance()->Set(base_key, root.toStyledString());
	}
	return true;
}
