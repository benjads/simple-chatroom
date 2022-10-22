#include <cstdio>

#include "server_worker.h"

ServerWorker::ServerWorker(int connfd) : connfd(connfd) {}
ServerWorker::~ServerWorker() = default;

void ServerWorker::execute() {
    printf("Client connected, FD: %d\n", connfd);
}
