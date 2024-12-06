#include "api/chat_api.h"
#include "database/database.h"

std::string server_address("localhost:65002");

void RunServer(Database &database) {
    ChatApiService service(database);

    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    auto server = builder.BuildAndStart();
    std::cout << "Chat Server listening on " << server_address << std::endl;
    server->Wait();
    std::cout << "Chat Server is shutting down!" << std::endl;
}

int main(int argc, char **argv) {
    Database db;
    RunServer(db);
    return 0;
}
