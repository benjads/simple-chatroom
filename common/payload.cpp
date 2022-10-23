#include "payload.h"

#include <utility>
#include "exception.h"

GatewayPacket::GatewayPacket(opcode op, std::string payload) : op(op), payload(std::move(payload)) {}

GatewayPacket::GatewayPacket(std::string raw) {
    try {
        auto j = json::parse(raw);
        op = j["op"];

        // TODO
        switch (op) {
            case CONNECT:
                break;
            case WELCOME:
                break;
        }

    } catch (json::parse_error &e) {
        throw MalformedPacketException(e.what());
    }
}

std::string GatewayPacket::serialize() {
    json j = {
            {"op", op},
            {"d",  data}
    };

    return j;
}

