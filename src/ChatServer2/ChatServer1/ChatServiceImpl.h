#pragma once
#include <grpcpp/grpcpp.h>
#include "message.grpc.pb.h"
#include "message.pb.h"
#include "data.h"
#include <mutex>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using message::ChatService;
using message::LoginReq;
using message::LoginRsp;
using message::GetChatServerRsp;

using message::AddFriendReq;
using message::AddFriendRsp;

using message::AuthFriendReq;
using message::AuthFriendRsp;

using message::TextChatMsgReq;
using message::TextChatMsgRsp;
using message::TextChatData;

class ChatServiceImpl final : public ChatService::Service
{
public:
	ChatServiceImpl() {}
	~ChatServiceImpl() {}
	Status NotifyAddFriend(ServerContext* context, const AddFriendReq* request, AddFriendRsp* response) override;
	Status NotifyAuthFriend(ServerContext* context, const AuthFriendReq* request, AuthFriendRsp* response) override;
	Status NotifyTextChatMsg(ServerContext* context, const TextChatMsgReq* request, TextChatMsgRsp* response) override;
	bool GetBaseInfo(std::string base_key, int uid, std::shared_ptr<UserInfo>& userinfo);
private:

};

