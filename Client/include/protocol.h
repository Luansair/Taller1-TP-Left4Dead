#ifndef PROTOCOL_H_
#define PROTOCOL_H_

#include <memory>
#include "../../Common/include/Socket/socket_game.h"
#include "../../Common/include/Information/information.h"
#include "../../Common/include/Information/feedback_server_creategame.h"
#include "../../Common/include/Information/feedback_server_gamestate.h"

class Protocol {
    GameSocket& socket;

    ElementStateDTO recvActorState();
    [[nodiscard]] std::shared_ptr<Information> builtCreateGameFeedback();
    [[nodiscard]] std::shared_ptr<Information> builtJoinGameFeedback();
    [[nodiscard]] std::shared_ptr<Information> builtGameStateFeedback();

public:
    explicit Protocol(GameSocket& socket);

    void sendAction(const Information& action);

    [[nodiscard]] std::shared_ptr<Information> recvFeedback();

    Protocol(const Protocol&) = delete;
    Protocol& operator=(const Protocol&) = delete;

    Protocol(Protocol&&) = default;
    Protocol& operator=(Protocol&&) = delete;

    ~Protocol() = default;
};

#endif  // PROTOCOL_H_