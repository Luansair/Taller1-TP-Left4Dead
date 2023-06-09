//
// Created by luan on 08/06/23.
//
#include "../../../include/Animations/LoopType/looptype_loopable.h"

void Loopable::fixIndex(std::uint8_t *sprite_index, std::size_t max_index) const {
    if (checkIndexOverflow(*sprite_index, max_index))
        *sprite_index = 0;
}

