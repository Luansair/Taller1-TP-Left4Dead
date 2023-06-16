//
// Created by luan on 05/06/23.
//
#include "../../include/Information/feedback_server_gamestate.h"
#include "../../include/Information/information_code.h"

GameStateFeedback::GameStateFeedback(
        std::vector<std::pair<std::uint16_t, ElementStateDTO>>
        &&elements) :
        elements(std::move(elements)) {
}

std::vector<int8_t> GameStateFeedback::serialize() const {
    using std::int8_t;
    using std::uint16_t;
    using std::vector;

    vector<int8_t> result;
    std::size_t byte_amount = elements.size() * (sizeof(ElementStateDTO) +
            sizeof(uint16_t));
    unsigned int vector_max_size = result.max_size();
    if (byte_amount < vector_max_size) {
        result.reserve(byte_amount);
    }

    // Push Feedback ID
    result.push_back(InformationID::FEEDBACK_GAME_STATE);

    // Push amount of actors/elements
    serializeNumber<uint16_t>(result, static_cast<uint16_t>(elements.size()));

    // Push information about element. Id and struct fields.
    for (const auto& element : elements) {
        const ElementStateDTO& dto = element.second;
        uint16_t actor_id = element.first;

        serializeNumber<uint16_t>(result, actor_id);
        result.push_back(static_cast<int8_t>(dto.type));
        result.push_back(static_cast<int8_t>(dto.action));
        result.push_back(static_cast<int8_t>(dto.direction));
        serializeNumber<std::int32_t>(result, dto.position_x);
        serializeNumber<std::int32_t>(result, dto.position_y);
    }

    return result;
}

