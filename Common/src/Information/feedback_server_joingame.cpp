//
// Created by luan on 16/06/23.
//
#include "../../include/Information/feedback_server_joingame.h"

JoinGameFeedback::JoinGameFeedback(std::uint8_t joined) : joined(joined) {

}

std::vector<std::int8_t> JoinGameFeedback::serialize() const {
    return {FEEDBACK_JOIN_GAME, static_cast<std::int8_t>(joined)};
}

