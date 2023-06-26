#ifndef TP_SCORE_DTO_H
#define TP_SCORE_DTO_H

#include <cstdint>

struct ScoreDTO {
    const std::uint16_t seconds_alive;
    const std::uint16_t kills;
    const std::uint32_t bullets_fired;


    ScoreDTO(ScoreDTO&&) = default;
    ScoreDTO& operator=(ScoreDTO&&) = delete;

    ScoreDTO(const ScoreDTO&) = delete;
    ScoreDTO& operator=(const ScoreDTO&) = delete;
};

#endif // TP_SCORE_DTO_H
