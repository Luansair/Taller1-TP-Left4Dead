#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "../../Common/include/socket.h"
#include "../../Common/include/action_dto.h"

class Protocol {
    Socket& socket;


public:
    explicit Protocol(Socket& socket);

    [[nodiscard]] Action* recvAction();
};

#endif  // PROTOCOL_H
