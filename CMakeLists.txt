cmake_minimum_required(VERSION 3.23)
project(simple_chatroom)

set(CMAKE_CXX_STANDARD 14)

add_executable(simple_chatroom_server server/server.cpp)
add_executable(simple_chatroom_client client/client.cpp)
