#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "../../Common/include/Socket/socket_game.h"
#include "../../Common/include/Information/information.h"
#include "Command/command_pregame.h"

class Protocol {
    GameSocket& socket;

public:
    explicit Protocol(GameSocket& socket);

    [[nodiscard]] PreGameCommand* recvPreGameCommand();

    [[nodiscard]] InGameCommand* recvInGameCommand(std::uint8_t player_id);

    void sendFeedback(const Information& feed);
};

#endif  // PROTOCOL_H
