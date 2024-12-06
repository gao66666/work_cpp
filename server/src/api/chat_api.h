#pragma once
#ifndef CHAT_API_H
#define CHAT_API_H

#include <list>

#include <grpc++/grpc++.h>

#include "api_chat.pb.h"
#include "api_chat.grpc.pb.h"

#include "../database/database.h"

#include "../logic/chat_manager.h"
#include "../logic/user_manager.h"


class ChatApiService final : public api::chat::ChatService::CallbackService {
public:
    explicit ChatApiService(const Database &database) :
            db(database),
            userManager(database), chatManager(database),
            _clients() {}

    grpc::ServerUnaryReactor *
    Login(::grpc::CallbackServerContext *context, const ::api::chat::UserCredentials *credentials, ::api::chat::None *none) override;

    grpc::ServerUnaryReactor *
    FetchChatList(::grpc::CallbackServerContext *context, const ::api::chat::None *none, ::api::chat::ChatList *list) override;

    grpc::ServerWriteReactor<api::chat::MessageList> *
    FetchMessageList(::grpc::CallbackServerContext *context, const ::api::chat::FetchMessageListRequest *request) override;

    grpc::ServerUnaryReactor *
    SendMessageTo(::grpc::CallbackServerContext *context, const ::api::chat::SendMessageRequest *request, ::api::chat::None *none) override;



private:

    class Client {
    public:
        virtual void NotifyNewMessage(uint64_t chat_id, const api::chat::Message &message) = 0;
    };

    void notifyClients(uint64_t chat_id, const api::chat::Message &message);

    Database db;
    UserManager userManager;
    ChatManager chatManager;
    std::list<Client *> _clients;

    class MessageStreamReactor;

    class ChatListReactor;
};


#endif //CHAT_API_H
