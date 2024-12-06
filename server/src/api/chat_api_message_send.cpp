#include <iostream>

#include "chat_api.h"

using namespace api::chat;


grpc::ServerUnaryReactor *
ChatApiService::SendMessageTo(grpc::CallbackServerContext *context, const SendMessageRequest *request, None *none) {
    auto reactor = context->DefaultReactor();

    // Authenticate user
    auto metadata = context->client_metadata();
    auto name = userManager.check_user_credentials(metadata);
    if (!name) {
        reactor->Finish(grpc::Status(grpc::StatusCode::UNAUTHENTICATED, "Invalid credentials"));
        return reactor;
    }

    // Check Messages
    auto id = request->target();
    auto messages = chatManager.get_messages_by_id(id);
    if (!messages) {
        reactor->Finish(grpc::Status(grpc::StatusCode::NOT_FOUND, "Chat Not Found"));
        return reactor;
    }
    //  Notify new messages to other clients
    auto *msg = messages.value()->add_messages();
    msg->set_sender_user_name(*name);
    msg->set_sender_user_id(0);
    *msg = request->message();
    notifyClients(id, *msg);

    reactor->Finish(grpc::Status::OK);
    return reactor;
}

void ChatApiService::notifyClients(uint64_t chat_id, const Message &message) {
    for (auto client: _clients) {
        client->NotifyNewMessage(chat_id, message);
    }
}

