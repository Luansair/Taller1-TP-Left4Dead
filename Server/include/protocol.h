#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "../../Common/include/Socket/socket_game.h"
#include "../../Common/include/Action/action.h"

class Protocol {
    GameSocket& socket;


public:
    explicit Protocol(GameSocket& socket);

    [[nodiscard]] Action* recvAction();
};

#endif  // PROTOCOL_H
