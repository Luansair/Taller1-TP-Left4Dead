#ifndef PROTOCOL_H_
#define PROTOCOL_H_

#include "../../Common/include/socket.h"

class Protocol {
    Socket& socket;

public:
    explicit Protocol(Socket& socket);

    void sendKeyPress(int event_type, int key_press);
    void sendEvent(int event_type);

    Protocol(const Protocol&) = delete;
    Protocol& operator=(const Protocol&) = delete;

    Protocol(Protocol&&) = default;
    Protocol& operator=(Protocol&&) = delete;

    ~Protocol() = default;
};

#endif  // PROTOCOL_H_