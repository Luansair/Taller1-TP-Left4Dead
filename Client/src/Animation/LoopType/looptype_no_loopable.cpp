//
// Created by luan on 08/06/23.
//
#include "../../../include/Animations/LoopType/looptype_no_loopable.h"

std::uint8_t NoLoopable::nextSprite(std::uint8_t sprite_index, std::size_t max_index) const {
    if (checkIndexOverflow(sprite_index, max_index))
        return max_index;
    else return sprite_index + 1;
}

