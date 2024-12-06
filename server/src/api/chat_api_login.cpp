#include <iostream>

#include "absl/strings/str_format.h"

#include "chat_api.h"

using namespace api::chat;

grpc::ServerUnaryReactor *
ChatApiService::Login(grpc::CallbackServerContext *context, const UserCredentials *credentials, None *none) {
    auto reactor = context->DefaultReactor();

    // Authenticate user
    auto metadata = context->client_metadata();
    auto name = userManager.check_user_credentials(metadata);
    if (!name) {
        absl::PrintF("Illegal user tried to login!\n");
        reactor->Finish(grpc::Status(grpc::StatusCode::UNAUTHENTICATED, "Invalid credentials"));
        return reactor;
    } else {
        absl::PrintF("User %s logged in\n", name.value());
        reactor->Finish(grpc::Status::OK);
        return reactor;
    }
}