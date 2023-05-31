#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "../../Common/include/socket.h"
#include "../../Common/include/Action/action.h"

class Protocol {
    Socket& socket;


public:
    explicit Protocol(Socket& socket);

    [[nodiscard]] Action* recvAction();
};

#endif  // PROTOCOL_H
