//
// Created by luan on 08/06/23.
//

#ifndef TP_LOOPTYPE_NO_LOOPABLE_H
#define TP_LOOPTYPE_NO_LOOPABLE_H

#include "looptype.h"

class NoLoopable : public LoopType {

public:
    NoLoopable() = default;

    void fixIndex(std::uint8_t* sprite_index, std::size_t max_index) const override;

    NoLoopable(NoLoopable&&) = default;
    NoLoopable& operator=(NoLoopable&&) = default;

    NoLoopable(const NoLoopable&) = delete;
    NoLoopable& operator=(const NoLoopable&) = delete;

    ~NoLoopable() override = default;
};
#endif //TP_LOOPTYPE_NO_LOOPABLE_H
