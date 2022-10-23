#ifndef SIMPLE_CHATROOM_SERVER_WORKER_H
#define SIMPLE_CHATROOM_SERVER_WORKER_H

#include <memory>
#include <mutex>
#include <thread>
#include "../common/payload.h"

#define FD_EMPTY (-100)

class ServerWorker {
public:
    explicit ServerWorker(int connfd);

    ~ServerWorker();

    void execute();
private:
    int connfd = FD_EMPTY;
    std::string nick;

    void check_recv();

    void send_packet(GatewayPacket packet);
};

#endif //SIMPLE_CHATROOM_SERVER_WORKER_H
