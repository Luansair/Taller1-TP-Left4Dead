#ifndef TP_FEEDBACK_SERVER_SCORE_H
#define TP_FEEDBACK_SERVER_SCORE_H

#include "../Information/information.h"
#include "score_dto.h"

class GameScoreFeedback : public Information {
public:
    const std::vector<std::pair<std::uint16_t, ScoreDTO>> score;

    explicit GameScoreFeedback(std::vector<std::pair<std::uint16_t, ScoreDTO>>&& score);

    [[nodiscard]] std::vector<int8_t> serialize() const override;

    [[nodiscard]] std::uint8_t get_type(void) const override;

    GameScoreFeedback(const GameScoreFeedback&) = delete;
    GameScoreFeedback operator=(const GameScoreFeedback&) = delete;

    ~GameScoreFeedback() override = default;
};

#endif //TP_FEEDBACK_SERVER_GAMESTATE_H
