#include "payload.h"

#include <utility>
#include "exception.h"

// class: GatewayPacket

GatewayPacket::GatewayPacket(opcode op, json payload) : op{op}, payload{std::move(payload)} {}

GatewayPacket::GatewayPacket(const std::string &raw) {
    try {
        auto j = json::parse(raw);
        this->op = j["op"];

        // TODO
        switch (this->op) {

        }

    } catch (json::parse_error &e) {
        throw MalformedPacketException(e.what());
    }
}

std::string GatewayPacket::serialize() {
    json j = {
            {"op", this->op},
            {"d",  this->payload}
    };

    return j.dump();
}

opcode GatewayPacket::getOp() const {
    return op;
}

const json &GatewayPacket::getPayload() const {
    return payload;
}

// class: Message

Message::Message(std::string sender, time_t timestamp, std::string body) : sender{std::move(sender)},
                                                                           timestamp{timestamp},
                                                                           body{std::move(body)} {}

Message::Message(const std::string &raw) {
    try {
        auto j = json::parse(raw);

        this->sender = j["sender"];
        this->timestamp = j["timestamp"];
        this->body = j["body"];
    } catch (json::parse_error &e) {
        throw MalformedPacketException(e.what());
    }
}

std::string Message::serialize() {
    json j = {
            {"sender", this->sender},
            {"timestamp", this->timestamp},
            {"body", this->body}
    };

    return j.dump();
}

const std::string &Message::getSender() const {
    return sender;
}

time_t Message::getTimestamp() const {
    return timestamp;
}

const std::string &Message::getBody() const {
    return body;
}

bool Message::operator==(const Message &rhs) const {
    return timestamp == rhs.timestamp;
}

bool Message::operator!=(const Message &rhs) const {
    return !(rhs == *this);
}
