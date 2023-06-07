#include <netinet/in.h>
#include "../include/protocol.h"
#include "../../Common/include/Information/information_code.h"
#define RECV_DATA(var) socket.recvData(&var, sizeof(var))
//------------------------PRIVATE METHODS-----------------------------------//

CreateGameFeedback *Protocol::builtCreateGameFeedback() {
    using std::uint32_t;

    uint32_t bigendian_game_code;
    socket.recvData(&bigendian_game_code, sizeof(bigendian_game_code));
    uint32_t game_code = ntohl(bigendian_game_code);
    return new CreateGameFeedback(game_code);
}

GameStateFeedback *Protocol::builtGameStateFeedback() {
    using std::uint8_t;
    using std::uint16_t;
    using std::size_t;
    using std::vector;
    using std::pair;

    size_t actors_amount = 0;
    RECV_DATA(actors_amount);

    vector<pair<uint16_t, ElementStateDTO>> actors;
    actors.reserve(actors_amount * sizeof(pair<uint16_t, ElementStateDTO>));

    for (size_t counter = 0; counter < actors_amount; counter++) {
        uint16_t bigendian_actor_id;
        RECV_DATA(bigendian_actor_id);
        uint16_t actor_id = ntohs(bigendian_actor_id);

        ElementStateDTO actor_state = recvActorState();

        actors.emplace_back(actor_id, actor_state);
    }
    return new GameStateFeedback(std::move(actors));
}

ElementStateDTO Protocol::recvActorState() {
    uint8_t actor_type;
    uint8_t actor_action;
    uint8_t actor_direction;
    int bigendian_actor_position_x;
    int bigendian_actor_position_y;

    RECV_DATA(actor_type);
    RECV_DATA(actor_action);
    RECV_DATA(actor_direction);
    RECV_DATA(bigendian_actor_position_x);
    RECV_DATA(bigendian_actor_position_y);

    int actor_position_x = static_cast<int>(ntohl(bigendian_actor_position_x));
    int actor_position_y = static_cast<int>(ntohl(bigendian_actor_position_y));

    return {actor_type, actor_action,actor_direction,
            actor_position_x,actor_position_y};

}

//------------------------PUBLIC METHODS------------------------------------//
Protocol::Protocol(GameSocket& socket) : socket(socket) {
}

void Protocol::sendAction(const Information &action) {
    std::vector<int8_t> action_vec = action.serialize();
    socket.sendData(action_vec.data(), action_vec.size());
}

Information *Protocol::recvFeedback() {
    Information* info = nullptr;
    std::uint8_t feedback_type;
    socket.recvData(&feedback_type, sizeof(feedback_type));

    if (feedback_type == InformationID::FEEDBACK_CREATE_GAME) {
        info = builtCreateGameFeedback();
    } else if (feedback_type == InformationID::FEEDBACK_GAME_STATE) {
        info = builtGameStateFeedback();
    }
    return info;
}
