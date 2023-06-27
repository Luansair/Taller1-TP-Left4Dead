//
// Created by luan on 08/06/23.
//

#ifndef TP_LOOPTYPE_LOOPABLE_H
#define TP_LOOPTYPE_LOOPABLE_H

#include "looptype.h"

class Loopable : public LoopType {
public:
    Loopable() = default;

    [[nodiscard]] std::uint8_t nextSprite(std::uint8_t sprite_index, std::size_t max_index) const override;

    Loopable(Loopable&&) = default;
    Loopable& operator=(Loopable&&) = default;

    Loopable(const Loopable&) = delete;
    Loopable& operator=(const Loopable&) = delete;

    ~Loopable() override = default;
};
#endif //TP_LOOPTYPE_LOOPABLE_H
