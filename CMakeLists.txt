cmake_minimum_required(VERSION 3.23)
project(simple_chatroom)

set(CMAKE_CXX_STANDARD 14)

add_executable(simple_chatroom_server server/server.cpp server/server_worker.cpp server/server_worker.h common/GatewayPacket.cpp common/GatewayPacket.h)
add_executable(simple_chatroom_client client/client.cpp common/GatewayPacket.cpp common/GatewayPacket.h)

include(CPM.cmake)
CPMAddPackage("gh:nlohmann/json@3.11.2")
target_link_libraries(simple_chatroom_server nlohmann_json::nlohmann_json)
