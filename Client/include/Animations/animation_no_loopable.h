//
// Created by luan on 08/06/23.
//

#ifndef TP_ANIMATION_NO_LOOPABLE_H
#define TP_ANIMATION_NO_LOOPABLE_H

#include "animation_loop_type.h"

class NoLoopable : public LoopType {

public:
    NoLoopable() = default;

    void fixIndex(std::uint8_t* sprite_index, std::size_t max_index) override;

    ~NoLoopable() = default;
};
#endif //TP_ANIMATION_NO_LOOPABLE_H
