#include <netinet/in.h>
#include <cstdlib>
#include <sys/socket.h>
#include <err.h>
#include <vector>
#include <queue>
#include <unistd.h>

#include "server_worker.h"

#define SERVER_PORT 8080

int create_listen_socket(uint16_t port) {
    struct sockaddr_in addr{};
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0) {
        err(EXIT_FAILURE, "socket error");
    }

    memset(&addr, 0, sizeof addr);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htons(INADDR_ANY);
    addr.sin_port = htons(port);
    if (bind(listenfd, (struct sockaddr *) &addr, sizeof addr) < 0) {
        err(EXIT_FAILURE, "bind error");
    }

    if (listen(listenfd, 500) < 0) {
        err(EXIT_FAILURE, "listen error");
    }

    return listenfd;
}

[[noreturn]] void process_clients(int listenfd) {
    std::vector<std::shared_ptr<ServerWorker>> workers;

    // Handle incoming clients
    while (true) {
        int connfd = accept(listenfd, nullptr, nullptr);
        if (connfd < 0) {
            warn("accept error");
            continue;
        }

        auto worker = std::make_shared<ServerWorker>(connfd);
        std::thread th(&ServerWorker::execute, worker);
        th.join();

        printf("[Server] Assigned worker to client FD %d\n", connfd);
    }
}

int main() {
    // Create socket
    auto listenfd = create_listen_socket(SERVER_PORT);

    // Listen for connections
    process_clients(listenfd);
}
