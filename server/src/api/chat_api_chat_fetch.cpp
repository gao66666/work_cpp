#include <iostream>

#include "absl/strings/str_format.h"

#include "chat_api.h"

using namespace api::chat;

class ChatApiService::ChatListReactor : public grpc::ServerUnaryReactor {
public:
    ChatListReactor(
            grpc::CallbackServerContext *context, ChatList *reply, ChatManager chatManager
    ) : _context(context) {
        const std::list<Chat> &allChats = chatManager.list_all_chats();
        for (const auto& chat: allChats) {
            Chat *newChat = pending.add_chats();
            newChat->set_id(chat.id());
            newChat->set_name(chat.name());
            newChat->set_is_group(chat.is_group());
            newChat->set_description(chat.description());
        }
        reply->Swap(&pending);
        Finish(grpc::Status::OK);
    }

    void OnDone() override {
        absl::PrintF("Completed to send Chat list!\n");
        delete this;
    }

    void OnCancel() override {
        absl::PrintF("Error when sending all chats\n");
        delete this;
    }

private:
    grpc::CallbackServerContext *_context;
    ChatList pending;
};


grpc::ServerUnaryReactor *
ChatApiService::FetchChatList(grpc::CallbackServerContext *context, const None *none, ChatList *list) {

    grpc::ServerUnaryReactor *reactor;

    // Authenticate user
    auto metadata = context->client_metadata();
    auto name = userManager.check_user_credentials(metadata);
    if (!name) {
        reactor = context->DefaultReactor();
        reactor->Finish(grpc::Status(grpc::StatusCode::UNAUTHENTICATED, "Invalid credentials"));
        return reactor;
    }
    absl::PrintF("Sending Chat list to %s \n", name.value());

    reactor = new ChatApiService::ChatListReactor(context, list, chatManager);

    return reactor;
}
