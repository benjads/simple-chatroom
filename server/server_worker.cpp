#include <cstdio>
#include <unistd.h>
#include <nlohmann/json.hpp>
#include <sys/socket.h>
#include <sys/poll.h>

#include "server_worker.h"
#include "../common/exception.h"

using json = nlohmann::json;

ServerWorker::ServerWorker(int connfd) : connfd{connfd} {}

ServerWorker::~ServerWorker() = default;

void ServerWorker::execute() {
    printf("Client connected, FD: %d\n", connfd);

    // Send welcome packet
    const GatewayPacket welcomePacket(WELCOME, nullptr);
    if (!send_packet(welcomePacket)) {
        // Failed, return
        return;
    }

    // Client poll/server event loop
    while (true) {
        // Check for new message from client
        if (!check_recv()) {
            // Failed, return
            return;
        }

        sleep(1000);

        // Check for new messages
    }
}

bool ServerWorker::check_recv() {
    struct pollfd fd {
            .fd =  this->connfd,
            .events = POLLIN
    };

    const int ret = poll(&fd, 1, 1000);
    switch (ret) {
        case -1:
            // Error
            printf("[FD: %d] Connection interrupted while polling for packet\n", this->connfd);
            close(this->connfd);
            return false;
        case 0:
            // Timeout
            return true;
        default:
            // Data to receive
            char buffer[120];
            ssize_t rdsize = recv(this->connfd, buffer, sizeof(buffer), 0);
            if (rdsize < 0) {
                // Connection closed/interrupted
                printf("[FD: %d] Connection interrupted while reading from client\n", this->connfd);
                close(this->connfd);
                return false;
            }

            try {
                GatewayPacket packet = GatewayPacket(buffer);
                handle_client_packet(packet);
            } catch (MalformedPacketException &e) {
                printf("[FD: %d] MalformedPacketException while reading from client\n", this->connfd);
                printf("%s\n", e.what());
            }

            return true;
    }
}

bool ServerWorker::send_packet(GatewayPacket packet) const {
    std::string payload = packet.serialize() + "\n";
    const auto plen = payload.length() + 1;
    const ssize_t wtsize = send(this->connfd, &payload, plen, 0);
    if (wtsize < 0) {
        // Connection closed/interrupted
        printf("[FD: %d] Connection interrupted while sending packet (opcode: %d)\n", this->connfd, packet.getOp());
        close(this->connfd);
        return false;
    }

    return true;
}

void ServerWorker::handle_client_packet(const GatewayPacket& packet) {
    switch(packet.getOp()) {
        case JOIN:
            method_join(packet);
        case WELCOME:
        case ONBOARD:
            // TODO invalid
            break;
    }
}

void ServerWorker::method_join(const GatewayPacket &packet) {
    const auto& payload = packet.getPayload();
    const std::string nick = payload["nick"];
    const auto nlen = nick.length();
    if (nlen < 1 || nlen > 12) {
        return;
    }

    this->client_nick = nick;
}

