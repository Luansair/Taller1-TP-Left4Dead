#ifndef PROTOCOL_H_
#define PROTOCOL_H_

#include "../../Common/include/socket.h"
#include "../../Common/include/action_dto.h"

class Protocol {
    Socket& socket;

public:
    explicit Protocol(Socket& socket);

    void sendAction(const Action& action);

    Protocol(const Protocol&) = delete;
    Protocol& operator=(const Protocol&) = delete;

    Protocol(Protocol&&) = default;
    Protocol& operator=(Protocol&&) = delete;

    ~Protocol() = default;
};

#endif  // PROTOCOL_H_