//
// Created by luan on 01/06/23.
//

#ifndef TP_STATE_DTO_ELEMENT_H
#define TP_STATE_DTO_ELEMENT_H

#include <cstdint>

struct ElementStateDTO {
    const std::uint8_t type;  // Ej: SOLDIER_IDF, ZOMBIE, ...
    const std::uint8_t action;  // Ej: ACTION_IDLE, ...
    const std::int8_t direction;
    const int position_x;
    const int position_y;
    const std::uint16_t health;
    const std::uint16_t actual_health;
    const std::uint16_t ammo;
    const std::uint16_t actual_ammo;
    const std::uint8_t time_left;
    const std::uint8_t is_dead;


    ElementStateDTO(ElementStateDTO&&) = default;
    ElementStateDTO& operator=(ElementStateDTO&&) = delete;

    ElementStateDTO(const ElementStateDTO&) = delete;
    ElementStateDTO& operator=(const ElementStateDTO&) = delete;
};

#endif // TP_STATE_DTO_ELEMENT_H
