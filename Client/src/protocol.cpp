#include <netinet/in.h>
#include "../include/protocol.h"
#include "../../Common/include/Information/information_code.h"
#include "../../Common/include/Information/feedback_server_joingame.h"

#define RECV_DATA(var) socket.recvData(&var, sizeof(var))
//------------------------PRIVATE METHODS-----------------------------------//

std::shared_ptr<Information> Protocol::builtCreateGameFeedback() {
    using std::uint32_t;
    using std::make_shared;

    uint32_t bigendian_game_code;
    socket.recvData(&bigendian_game_code, sizeof(bigendian_game_code));
    uint32_t game_code = ntohl(bigendian_game_code);
    return make_shared<CreateGameFeedback>(game_code);
}

std::shared_ptr<Information> Protocol::builtJoinGameFeedback() {
    using std::uint8_t;
    using std::make_shared;

    uint8_t joined;

    RECV_DATA(joined);
    return make_shared<JoinGameFeedback>(joined);
}

std::shared_ptr<Information> Protocol::builtGameStateFeedback() {
    using std::uint8_t;
    using std::uint16_t;
    using std::uint32_t;
    using std::size_t;
    using std::vector;
    using std::pair;
    using std::make_shared;

    uint16_t bigendian_actors_amount = 0;
    RECV_DATA(bigendian_actors_amount);
    uint16_t actors_amount = ntohs(bigendian_actors_amount);

    vector<pair<uint16_t, ElementStateDTO>> actors;
    actors.reserve(actors_amount * sizeof(pair<uint16_t, ElementStateDTO>));

    for (size_t counter = 0; counter < actors_amount; counter++) {
        uint16_t bigendian_actor_id;
        RECV_DATA(bigendian_actor_id);
        uint16_t actor_id = ntohs(bigendian_actor_id);

        ElementStateDTO&& actor_state = recvActorState();

        actors.emplace_back(actor_id, std::move(actor_state));
    }
    return make_shared<GameStateFeedback>(std::move(actors));
}

ElementStateDTO Protocol::recvActorState() {
    uint8_t actor_type;
    uint8_t actor_action;
    int8_t actor_direction;
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

[[nodiscard]] std::shared_ptr<Information> Protocol::recvFeedback() {
    std::uint8_t feedback_type;
    socket.recvData(&feedback_type, sizeof(feedback_type));

    if (feedback_type == InformationID::FEEDBACK_CREATE_GAME) {
        return builtCreateGameFeedback();
    } else if (feedback_type == InformationID::FEEDBACK_JOIN_GAME) {
        return builtJoinGameFeedback();
    } else if (feedback_type == InformationID::FEEDBACK_GAME_STATE) {
        return builtGameStateFeedback();
    }
    return nullptr;
}
