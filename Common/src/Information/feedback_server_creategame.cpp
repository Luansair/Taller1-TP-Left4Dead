//
// Created by luan on 04/06/23.
//
#include "../../include/Information/feedback_server_creategame.h"
#include "../../include/Information/information_code.h"

CreateGameFeedback::CreateGameFeedback(std::uint32_t game_code) :
    game_code(game_code) {
}

std::vector<std::int8_t> CreateGameFeedback::serialize() const {
    using std::int8_t;
    using std::vector;

    vector<int8_t> result;
    result.reserve(5);

    result.push_back(static_cast<int8_t>(InformationID::FEEDBACK_CREATE_GAME));
    serializeNumber(result, game_code);
    return result;
}

std::uint8_t CreateGameFeedback::get_type(void) const {
    return FEEDBACK_CREATE_GAME;
}

