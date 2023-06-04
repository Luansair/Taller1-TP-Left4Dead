#include <netinet/in.h>
#include "../include/protocol.h"
#include "../../Common/include/Action/action_code.h"
#include "../include/Command/command_pregame_joingame.h"
#include "../include/Command/command_pregame_creategame.h"
#include "../include/Command/command_ingame_startshoot.h"

Protocol::Protocol(GameSocket &socket) : socket(socket) {}


PreGameCommand *Protocol::recvPreGameCommand() {
    std::uint8_t action_id;
    socket.recvData(&action_id, 1);
    if (action_id == ActionID::JOIN) {
        std::uint32_t bigendian_game_code;
        socket.recvData(&bigendian_game_code, sizeof(bigendian_game_code));
        std::uint32_t game_code = ntohl(bigendian_game_code);
        return new JoinGameCommand(game_code);
    } else if (action_id == ActionID::CREATE) {
        return new CreateGameCommand();
    }
    return nullptr;
}

InGameCommand* Protocol::recvInGameCommand(std::uint8_t player_id) {
    uint8_t action_id;
    socket.recvData(&action_id, 1);
    if (action_id == SHOOT) {
        uint8_t action_state;
        socket.recvData(&action_state, 1);
        if (action_state == ON) {
            return new StartShootCommand(player_id);
        }
    }
    return nullptr;
}