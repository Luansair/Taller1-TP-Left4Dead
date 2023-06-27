//
// Created by luan on 08/06/23.
//
#include "../../../include/Animations/LoopType/looptype.h"

bool LoopType::checkIndexOverflow(std::uint8_t sprite_index,
                                  std::size_t max_index) const {
    return sprite_index >= max_index;
}

