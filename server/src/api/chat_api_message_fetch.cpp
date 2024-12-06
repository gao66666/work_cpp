#include <iostream>

#include "absl/strings/str_format.h"

#include "chat_api.h"

using namespace api::chat;


class ChatApiService::MessageStreamReactor : public grpc::ServerWriteReactor<MessageList>, ChatApiService::Client {
public:
    MessageStreamReactor(ChatApiService *service, grpc::CallbackServerContext *context, const FetchMessageListRequest *request)
            : _service(service), _context(context), _request(request) {}

    void Start() {

        // Authenticate user
        auto metadata = _context->client_metadata();
        auto name = _service->userManager.check_user_credentials(metadata);
        if (!name) {
            this->Finish(grpc::Status(grpc::StatusCode::UNAUTHENTICATED, "Invalid credentials"));
            delete this;
            absl::PrintF("Illegal user tried to login!\n");
            return;
        }

        // Register user
        _username = *name;
        _connected = true;
        _service->_clients.push_back(this);
        absl::PrintF("User %s connected to Chat(id: %u)\n", name.value(), _request->chat_id());

        // Update messages

        uint64_t target_chat = _request->chat_id();
        auto messages = _service->chatManager.get_messages_by_id(target_chat);

        if (!messages) {
            this->Finish(grpc::Status(grpc::StatusCode::NOT_FOUND, "Chat Not Found"));
            delete this;
            return;
        }

        _writing = true;
        absl::PrintF("Sending Chat Messages(id: %u) to %s\n", target_chat, name.value());
        StartWrite(messages.value());
    }


    void OnWriteDone(bool ok) override {
        if (!ok || !_connected) {
            _connected = false;
            _service->_clients.remove(this);
            absl::PrintF("Error occurs! (user: %s, ok: %d, connected: %d)\n", _username.c_str(), ok, _connected);
            return;
        }

        // Prepare for the next write (if needed)
        if (!_pendingMessages.empty()) {
            absl::PrintF("Sending updated messages to %s\n", _username.c_str());
            _writing = true;
            StartWrite(&(_pendingMessages.front()));
            _pendingMessages.pop_front();
        } else {
            _writing = false;
            absl::PrintF("Completed to send messages to %s\n", _username.c_str());
        }
    }

    void OnDone() override {
        absl::PrintF("User %s terminated from Chat(id: %u)\n", _username.c_str(), _request->chat_id());
        _connected = false;
        _service->_clients.remove(this);
        this->Finish(grpc::Status::OK);
        delete this;
    }

    void OnCancel() override {
        absl::PrintF("User %s disconnected from Chat(id: %u)\n", _username.c_str(), _request->chat_id());
        _connected = false;
    }

    void NotifyNewMessage(uint64_t chat_id, const Message &message) override {
        if (!_connected) return;

        if (chat_id != _request->chat_id()) return;


        MessageList messages;
        *messages.add_messages() = message;

        if (_writing) {
            absl::PrintF("Notify new message (chat %u) to %s (pending)\n", chat_id, _username.c_str());
            _pendingMessages.push_back(messages);
        } else {
            absl::PrintF("Notify new message (chat %u) to %s\n", chat_id, _username.c_str());
            _writing = true;
            StartWrite(&messages);
        }
    }

private:

    ChatApiService *_service;
    grpc::CallbackServerContext *_context;
    const FetchMessageListRequest *_request;

    std::string _username;

    bool _connected = false;
    bool _writing = false;
    std::list<MessageList> _pendingMessages;
};

grpc::ServerWriteReactor<api::chat::MessageList> *
ChatApiService::FetchMessageList(grpc::CallbackServerContext *context, const FetchMessageListRequest *request) {
    auto reactor = new ChatApiService::MessageStreamReactor(this, context, request);
    reactor->Start();
    return reactor;
}
