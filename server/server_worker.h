#ifndef SIMPLE_CHATROOM_SERVER_WORKER_H
#define SIMPLE_CHATROOM_SERVER_WORKER_H

#include <memory>
#include <mutex>
#include <thread>
#include <list>
#include "../common/payload.h"

#define FD_EMPTY (-100)

typedef struct {
    std::list<Message> messages;
    std::mutex mutex;
} *MessageContainer;

class ServerWorker {
public:
    ServerWorker(int connfd, MessageContainer msg_cont);

    ~ServerWorker();

    void execute();

private:
    int connfd = FD_EMPTY;
    MessageContainer msg_cont;
    std::list<Message>::iterator last_msg;
    std::string client_nick;

    bool check_recv();

    void check_msgs();

    bool send_packet(GatewayPacket packet) const;

    void handle_client_packet(const GatewayPacket &packet);

    void method_join(const GatewayPacket &packet);
};

#endif //SIMPLE_CHATROOM_SERVER_WORKER_H
