//
// Created by luan on 05/06/23.
//
#include "../../include/Information/feedback_server_gamestate.h"
#include "../../include/Information/information_code.h"

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
    result.push_back(InformationID::FEEDBACK_GAME_STATE);
    for (const auto& element : elements) {
        const ElementStateDTO& dto = element.second;

        serializeNumber(result, dto.id);
        result.push_back(static_cast<int8_t>(dto.type));
        result.push_back(static_cast<int8_t>(dto.action));
        result.push_back(static_cast<int8_t>(dto.direction));
        serializeNumber(result, dto.position_x);
        serializeNumber(result, dto.position_y);
    }

    return result;
}

