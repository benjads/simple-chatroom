#include <cstdio>
#include <nlohmann/json.hpp>

#include "server_worker.h"

using json = nlohmann::json;

ServerWorker::ServerWorker(int connfd) : connfd(connfd) {}
ServerWorker::~ServerWorker() = default;

void ServerWorker::execute() {
    printf("Client connected, FD: %d\n", connfd);

}
