//
// Created by luan on 08/06/23.
//
#include "../../include/Animations/animation_loop_type.h"

bool LoopType::checkIndexOverflow(std::uint8_t sprite_index,
                                  std::size_t max_index) {
    return sprite_index > max_index;
}

