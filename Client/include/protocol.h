#ifndef PROTOCOL_H_
#define PROTOCOL_H_

#include "../../Common/include/Socket/socket_game.h"
#include "../../Common/include/Information/information.h"

class Protocol {
    GameSocket& socket;

public:
    explicit Protocol(GameSocket& socket);

    void sendAction(const Information& action);

    [[nodiscard]] Information* recvPreGameFeedback();

    Protocol(const Protocol&) = delete;
    Protocol& operator=(const Protocol&) = delete;

    Protocol(Protocol&&) = default;
    Protocol& operator=(Protocol&&) = delete;

    ~Protocol() = default;
};

#endif  // PROTOCOL_H_