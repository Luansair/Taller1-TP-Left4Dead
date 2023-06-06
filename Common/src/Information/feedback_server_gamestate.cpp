//
// Created by luan on 05/06/23.
//
#include "../../include/Information/feedback_server_gamestate.h"

GameStateFeedback::GameStateFeedback(
        std::vector<std::pair<std::uint32_t, ElementStateDTO>>
        &&elements) :
        elements(std::move(elements)) {
}

std::vector<int8_t> GameStateFeedback::serialize() const {
    using std::int8_t;
    using std::vector;

    vector<int8_t> result;
    result.reserve(elements.size());


    return result;
}

