//
// Created by luan on 08/06/23.
//
#include "../../include/Animations/animation_loopable.h"

void Loopable::fixIndex(std::uint8_t *sprite_index, std::size_t max_index) {
    if (checkIndexOverflow(*sprite_index, max_index))
        *sprite_index = 0;
}

