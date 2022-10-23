#ifndef SIMPLE_CHATROOM_EXCEPTION_H
#define SIMPLE_CHATROOM_EXCEPTION_H

#include <exception>

class MalformedPacketException : public std::exception {
private:
    const char *cause;

public:
    explicit MalformedPacketException(const char *cause) : cause(cause) {}
    const char *what() {
        return cause;
    }
};

#endif //SIMPLE_CHATROOM_EXCEPTION_H
