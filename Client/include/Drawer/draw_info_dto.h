//
// Created by luan on 02/06/23.
//

#ifndef TP_DRAW_INFO_DTO_H
#define TP_DRAW_INFO_DTO_H

#include <cstdint>

struct DrawInfoDTO {
    const int position_x;
    const int position_y;
    const std::uint8_t direction;
};

#endif //TP_DRAW_INFO_DTO_H
