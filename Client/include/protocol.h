#ifndef PROTOCOL_H_
#define PROTOCOL_H_

#include "../../Common/include/Socket/socket_game.h"
#include "../../Common/include/Action/action.h"
#include "../../Common/include/Feedback/feedback_server.h"

class Protocol {
    GameSocket& socket;

public:
    explicit Protocol(GameSocket& socket);

    void sendAction(const Action& action);

    [[nodiscard]] ServerFeedback* recvPreGameFeedback();

    Protocol(const Protocol&) = delete;
    Protocol& operator=(const Protocol&) = delete;

    Protocol(Protocol&&) = default;
    Protocol& operator=(Protocol&&) = delete;

    ~Protocol() = default;
};

#endif  // PROTOCOL_H_