#ifndef SIMPLE_CHATROOM_PAYLOAD_H
#define SIMPLE_CHATROOM_PAYLOAD_H

#include <nlohmann/json.hpp>

using json = nlohmann::json;
//using seconds_t = std::chrono::seconds;

enum opcode {
    WELCOME = 0x01,
    JOIN = 0x02,
    ONBOARD = 0x03
};

class JsonSerializable {
    virtual std::string serialize() = 0;
};

class GatewayPacket : public JsonSerializable {
public:
    GatewayPacket(opcode op, json rawPayload);

    explicit GatewayPacket(const std::string& raw);

    std::string serialize() override;

private:
    opcode op;
    json payload;
};

class Message : public JsonSerializable {
public:
    Message(std::string sender, time_t timestamp, std::string body);

    explicit Message(const std::string& raw);

    std::string serialize() override;

private:
    std::string sender;
    time_t timestamp;
    std::string body;
};

#endif //SIMPLE_CHATROOM_PAYLOAD_H
