#include <netinet/in.h>
#include "../include/protocol.h"
#include "../../Common/include/Information/information_code.h"
#include "../../Common/include/Information/feedback_server_joingame.h"
#include <iostream>

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
    uint16_t bigendian_actor_health;
    uint16_t bigendian_actor_actual_health;
    uint16_t bigendian_actor_ammo;
    uint16_t bigendian_actor_actual_ammo;
    uint8_t actor_time_left;
    uint8_t actor_is_dead;

    RECV_DATA(actor_type);
    RECV_DATA(actor_action);
    RECV_DATA(actor_direction);
    RECV_DATA(bigendian_actor_position_x);
    RECV_DATA(bigendian_actor_position_y);
    RECV_DATA(bigendian_actor_health);
    RECV_DATA(bigendian_actor_actual_health);
    RECV_DATA(bigendian_actor_ammo);
    RECV_DATA(bigendian_actor_actual_ammo);
    RECV_DATA(actor_time_left);
    RECV_DATA(actor_is_dead);

    int actor_position_x = static_cast<int>(ntohl(bigendian_actor_position_x));
    int actor_position_y = static_cast<int>(ntohl(bigendian_actor_position_y));
    uint16_t actor_health = static_cast<uint16_t>(ntohs(bigendian_actor_health));
    uint16_t actor_actual_health = static_cast<uint16_t>(ntohs(bigendian_actor_actual_health));
    uint16_t actor_ammo = static_cast<uint16_t>(ntohs(bigendian_actor_ammo));
    uint16_t actor_actual_ammo = static_cast<uint16_t>(ntohs(bigendian_actor_actual_ammo));
    return {actor_type, actor_action,actor_direction,
            actor_position_x,actor_position_y, actor_health, actor_actual_health, actor_ammo, actor_actual_ammo, actor_time_left, actor_is_dead};

}

std::shared_ptr<Information> Protocol::builtGameScoreFeedback() {
    using std::uint8_t;
    using std::uint16_t;
    using std::uint32_t;
    using std::size_t;
    using std::vector;
    using std::pair;
    using std::make_shared;

    uint16_t bigendian_scores_amount = 0;
    RECV_DATA(bigendian_scores_amount);
    uint16_t scores_amount = ntohs(bigendian_scores_amount);

    vector<pair<uint16_t, ScoreDTO>> scores;
    scores.reserve(scores_amount * sizeof(pair<uint16_t, ScoreDTO>));

    for (size_t counter = 0; counter < scores_amount; counter++) {
        uint16_t bigendian_player_id;
        RECV_DATA(bigendian_player_id);
        uint16_t player_id = ntohs(bigendian_player_id);

        ScoreDTO&& player_score = recvScore();

        scores.emplace_back(player_id, std::move(player_score));
    }
    return make_shared<GameScoreFeedback>(std::move(scores));
}

ScoreDTO Protocol::recvScore() {

    uint16_t bigendian_seconds_alive;
    uint16_t bigendian_kills;
    uint32_t bigendian_bullets_fired;

    RECV_DATA(bigendian_seconds_alive);
    RECV_DATA(bigendian_kills);
    RECV_DATA(bigendian_bullets_fired);

    uint16_t seconds_alive = static_cast<uint16_t>(ntohs(bigendian_seconds_alive));
    uint16_t kills = static_cast<uint16_t>(ntohs(bigendian_kills));
    int bullets_fired = static_cast<int>(ntohl(bigendian_bullets_fired));
    return {seconds_alive, kills, bullets_fired};

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
    } else if (feedback_type == InformationID::FEEDBACK_GAME_SCORE) {
        return builtGameScoreFeedback();
    }
    return nullptr;
}
