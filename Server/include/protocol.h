#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "../../Common/include/socket.h"

class Protocol {
    Socket& socket;

public:
    explicit Protocol(Socket& socket);
};

#endif  // PROTOCOL_H
