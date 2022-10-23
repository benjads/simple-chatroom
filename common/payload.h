#ifndef SIMPLE_CHATROOM_PAYLOAD_H
#define SIMPLE_CHATROOM_PAYLOAD_H

#include <nlohmann/json.hpp>

using json = nlohmann::json;

enum opcode {
    CONNECT = 0x01,
    WELCOME = 0x02,
};

template <typename T>
class JsonSerializable {
    virtual std::string serialize() = 0;
};

class GatewayPacket : public JsonSerializable<GatewayPacket> {
public:
    GatewayPacket(opcode op, std::string payload);
    GatewayPacket(std::string raw);
    std::string serialize() override;
private:
    opcode op;
    std::string payload;
};

#endif //SIMPLE_CHATROOM_PAYLOAD_H
