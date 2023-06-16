#include <netinet/in.h>
#include "../include/protocol.h"
#include "../../Common/include/Information/information_code.h"
#include "../include/Command/command_pregame_joingame.h"
#include "../include/Command/command_pregame_creategame.h"
#include "../include/Command/command_ingame_startshoot.h"
#include "../include/Command/command_ingame_startmove.h"
#include "../include/Command/command_ingame_startidle.h"

Protocol::Protocol(GameSocket &socket) : socket(socket) {}


PreGameCommand *Protocol::recvPreGameCommand() {
    std::uint8_t action_id;
    socket.recvData(&action_id, 1);

    if (action_id == InformationID::REQUEST_JOIN_GAME) {
        std::uint32_t bigendian_game_code;
        socket.recvData(&bigendian_game_code, sizeof(bigendian_game_code));
        std::uint32_t game_code = ntohl(bigendian_game_code);
        return new JoinGameCommand(game_code);

    } else if (action_id == InformationID::REQUEST_CREATE_GAME) {
        return new CreateGameCommand();
    }
    return nullptr;
}

InGameCommand* Protocol::recvInGameCommand(std::uint8_t player_id) {
    using std::uint8_t;
    using std::int8_t;

    uint8_t action_id;
    socket.recvData(&action_id, 1);
    if (action_id == ACTION_SHOOT) {
        uint8_t action_state;
        socket.recvData(&action_state, 1);
        if (action_state == ON) {
            return new StartShootCommand(player_id);
        }
    } else if (action_id == ACTION_MOVE) {
        uint8_t action_state;
        uint8_t axis = X;
        int8_t direction;
        uint8_t force = NORMAL;
        socket.recvData(&action_state, 1);
        socket.recvData(&direction, 1);
        if (action_state == ON) {
            return new StartMoveCommand(player_id, axis, direction, force);
        } else if (action_state == OFF) {
            return new StartIdleCommand(player_id);
        }
    }
    return nullptr;
}

void Protocol::sendFeedback(const Information& feed) {
    // SegFault
    std::vector<int8_t> feedback_vec = feed.serialize();
    socket.sendData(feedback_vec.data(), feedback_vec.size());
}
