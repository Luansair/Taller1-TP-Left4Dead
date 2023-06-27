#ifndef TP_SCORE_DTO_H
#define TP_SCORE_DTO_H

#include <cstdint>

struct ScoreDTO {
    const std::uint16_t seconds_alive;
    const std::uint16_t kills;
    const int bullets_fired;
};

#endif // TP_SCORE_DTO_H
