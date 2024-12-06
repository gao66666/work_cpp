cmake_minimum_required(VERSION 3.21)

project(gRPC-Chat-Server C CXX)
set(CMAKE_CXX_STANDARD 17)

include(cmake/find_grpc.cmake)
include(cmake/compile_grpc_proto.cmake)

####################################################################

compile_grpc_proto(grpc_proto_chat api_chat "src/api/api_chat.proto")

set(CPP_SOURCES
    src/server.cpp
    src/api/chat_api_login.cpp
    src/api/chat_api_chat_fetch.cpp
    src/api/chat_api_message_fetch.cpp
    src/api/chat_api_message_send.cpp
    src/logic/chat_manager.cpp
    src/logic/user_manager.cpp
    )

set(CPP_HEADER
    src/api/chat_api.h
    src/logic/chat_manager.h
    src/logic/user_manager.h
    )


####################################################################

add_executable(chat_server
    src/server.cpp
    src/api/chat_api.h
    src/api/chat_api_login.cpp
    src/api/chat_api_chat_fetch.cpp
    src/api/chat_api_message_fetch.cpp
    src/api/chat_api_message_send.cpp
    src/logic/chat_manager.h
    src/logic/chat_manager.cpp
    src/logic/user_manager.h
    src/logic/user_manager.cpp
    src/database/database.h
    src/database/database.cpp
    )

target_link_libraries(
    chat_server
    absl::str_format
    ${_GRPC_GRPCPP}
    ${_PROTOBUF_LIBPROTOBUF}
    grpc_proto_chat
)


####################################################################