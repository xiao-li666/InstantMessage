#include "ChatServiceImpl.h"
#include "const.h"
#include "UserMgr.h"
#include "CSession.h"

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
    return Status::OK;
}

Status ChatServiceImpl::NotifyTextChatMsg(ServerContext* context, const TextChatMsgReq* request, TextChatMsgRsp* response)
{
    return Status::OK;
}

bool ChatServiceImpl::GetBaseInfo(std::string base_key, int uid, std::shared_ptr<UserInfo>& userinfo)
{
    return true;
}
