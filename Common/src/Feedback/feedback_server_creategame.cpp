//
// Created by luan on 04/06/23.
//
#include "../../include/Feedback/feedback_server_creategame.h"
#include "../../include/Feedback/feedback_code.h"
#include "../../include/serializer.h"

CreateGameFeedback::CreateGameFeedback(std::uint32_t game_code) :
    game_code(game_code) {
}

std::vector<std::int8_t> CreateGameFeedback::serialize() const {
    using std::int8_t;
    using std::vector;

    vector<int8_t> result;
    result.reserve(5);

    result.push_back(static_cast<int8_t>(FeedbackType::FEED_CREATE));
    Serializer::serializeFourBytesNumber(result, game_code);
    return result;
}

