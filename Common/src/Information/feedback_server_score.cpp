#include "../../include/Information/feedback_server_score.h"
#include "../../include/Information/information_code.h"

GameScoreFeedback::GameScoreFeedback(
        std::vector<std::pair<std::uint16_t, ScoreDTO>>
        &&score) :
        score(std::move(score)) {
}

std::vector<int8_t> GameScoreFeedback::serialize() const {
    using std::int8_t;
    using std::uint16_t;
    using std::vector;

    vector<int8_t> result;
    std::size_t byte_amount = score.size() * (sizeof(ScoreDTO) +
            sizeof(uint16_t));
    unsigned int vector_max_size = result.max_size();
    if (byte_amount < vector_max_size) {
        result.reserve(byte_amount);
    }

    // Push Feedback ID
    result.push_back(InformationID::FEEDBACK_GAME_SCORE);

    // Push amount of actors/scores
    serializeNumber<uint16_t>(result, static_cast<uint16_t>(score.size()));

    // Push information about element. Id and struct fields.
    for (const auto& element : score) {
        const ScoreDTO& dto = element.second;
        uint16_t player_id = element.first;

        serializeNumber<uint16_t>(result, player_id);
        serializeNumber<uint16_t>(result, dto.seconds_alive);
        serializeNumber<uint16_t>(result, dto.kills);
        serializeNumber<uint32_t>(result, dto.bullets_fired);
    }

    return result;
}


std::uint8_t GameScoreFeedback::get_type(void) const {
    return FEEDBACK_GAME_SCORE;
}