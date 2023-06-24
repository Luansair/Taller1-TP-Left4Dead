#include <netinet/in.h>
#include "../include/protocol.h"
#include "../include/Command/command_pregame_joingame.h"
#include "../include/Command/command_pregame_creategame.h"
#include "../include/Command/command_ingame_startshoot.h"
#include "../include/Command/command_ingame_startchange.h"
#include "../include/Command/command_ingame_startmove.h"
#include "../include/Command/command_ingame_startthrow.h"
#include "../include/Command/command_ingame_startidle.h"
#include "../include/Command/command_ingame_startrevive.h"
#include "../include/Command/command_ingame_pick_soldier.h"

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
        uint8_t gamemode;
        uint8_t gamedif;
        socket.recvData(&gamemode, 1);
        socket.recvData(&gamedif, 1);
        if (gamemode == InformationID::REQUEST_SURVIVAL) {
            if (gamedif == REQUEST_EASY) return new CreateGameCommand(SURVIVAL, DEASY);
            if (gamedif == REQUEST_NORMAL) return new CreateGameCommand(SURVIVAL, DNORMAL);
            if (gamedif == REQUEST_HARD) return new CreateGameCommand(SURVIVAL, DHARD);
            if (gamedif == REQUEST_INSANE) return new CreateGameCommand(SURVIVAL, DINSANE);
        } else if (gamemode == REQUEST_CLEAR_THE_ZONE) {
            if (gamedif == REQUEST_EASY) return new CreateGameCommand(CLEAR_THE_ZONE, DEASY);
            if (gamedif == REQUEST_NORMAL) return new CreateGameCommand(CLEAR_THE_ZONE, DNORMAL);
            if (gamedif == REQUEST_HARD) return new CreateGameCommand(CLEAR_THE_ZONE, DHARD);
            if (gamedif == REQUEST_INSANE) return new CreateGameCommand(CLEAR_THE_ZONE, DINSANE);
        }
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
        } else if (action_state == OFF) {
            return new StartIdleCommand(player_id);
        }
    } else if (action_id == ACTION_MOVE) {
        uint8_t action_state;
        uint8_t axis;
        int8_t direction;
        uint8_t force;
        socket.recvData(&action_state, 1);
        socket.recvData(&axis, 1);
        socket.recvData(&direction, 1);
        socket.recvData(&force, 1);
        if (action_state == ON) {
            return new StartMoveCommand(player_id, axis, direction, force);
        } else if (action_state == OFF) {
            return new StartIdleCommand(player_id);
        }
    } else if (action_id == ACTION_REVIVE) {
        uint8_t action_state;
        socket.recvData(&action_state, 1);
        if (action_state == ON) {
            return new StartReviveCommand(player_id);
        } else if (action_state == OFF) {
            return new StartIdleCommand(player_id);
        }  
    } else if (action_id == ACTION_THROW) {
        uint8_t action_state;
        socket.recvData(&action_state, 1);
        if (action_state == ON) {
            return new StartThrowCommand(player_id);
        } else if (action_state == OFF) {
            return new StartIdleCommand(player_id);
        }
    } else if (action_id == ACTION_CHANGE) {
        uint8_t action_state;
        socket.recvData(&action_state, 1);
        if (action_state == ON) {
            return new StartChangeCommand(player_id);
        } else if (action_state == OFF) {
            return new StartIdleCommand(player_id);
        } 
    } else if (action_id == REQUEST_PICK_P90_SOLDIER) {
        return new PickSoldierCommand(player_id, SOLDIER_P90);
    } else if (action_id == REQUEST_PICK_IDF_SOLDIER) {
        return new PickSoldierCommand(player_id, SOLDIER_IDF);
    } else if (action_id == REQUEST_PICK_SCOUT_SOLDIER) {
        return new PickSoldierCommand(player_id, SOLDIER_SCOUT);
    }
    return nullptr;
}

void Protocol::sendFeedback(const Information& feed) {
    // SegFault
    std::vector<int8_t> feedback_vec = feed.serialize();
    socket.sendData(feedback_vec.data(), feedback_vec.size());
}
