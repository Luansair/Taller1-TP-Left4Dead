//
// Created by luan on 01/06/23.
//

#ifndef TP_STATE_PLAYER_DTO_H
#define TP_STATE_PLAYER_DTO_H

#include <cstdint>

struct PlayerStateDTO {
    const std::uint8_t action;
    const std::uint8_t direction;
    const int position_x;
    const int position_y;
};

#endif // TP_STATE_PLAYER_DTO_H
