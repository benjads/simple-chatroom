#ifndef SIMPLE_CHATROOM_PAYLOAD_H
#define SIMPLE_CHATROOM_PAYLOAD_H

#include <nlohmann/json.hpp>

using json = nlohmann::json;
//using seconds_t = std::chrono::seconds;

enum opcode {
    WELCOME = 0x01,
    JOIN = 0x02,
    ONBOARD = 0x03,
    SEND_MSG = 0x04,
    SEND_MSG_ACK = 0x05,
    NEW_MSGS = 0x06
};

class JsonSerializable {
    virtual std::string serialize() = 0;
};

class GatewayPacket : public JsonSerializable {
public:
    GatewayPacket(opcode op, json rawPayload);

    explicit GatewayPacket(const std::string& raw);

    std::string serialize() override;

    opcode getOp() const;

    const json &getPayload() const;

private:
    opcode op;
    json payload;
};

class Message : public JsonSerializable {
public:
    Message(std::string sender, time_t timestamp, std::string body);

    explicit Message(const std::string& raw);

    bool operator==(const Message &rhs) const;

    bool operator!=(const Message &rhs) const;

    std::string serialize() override;

    const std::string &getSender() const;

    time_t getTimestamp() const;

    const std::string &getBody() const;

private:
    std::string sender;
    time_t timestamp;
    std::string body;
};

#endif //SIMPLE_CHATROOM_PAYLOAD_H
