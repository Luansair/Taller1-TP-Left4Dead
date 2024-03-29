//
// Created by luan on 08/06/23.
//

#ifndef TP_LOOPTYPE_H
#define TP_LOOPTYPE_H

#include <cstdint>

class LoopType {
protected:
    [[nodiscard]] bool checkIndexOverflow(std::uint8_t sprite_index, std::size_t max_index) const;
    LoopType() = default;
public:
    [[nodiscard]] virtual std::uint8_t nextSprite(std::uint8_t sprite_index, std::size_t max_index) const = 0;

    LoopType(LoopType&&) = default;
    LoopType& operator=(LoopType&&) = default;

    LoopType(const LoopType&) = delete;
    LoopType& operator=(const LoopType&) = delete;

    virtual ~LoopType() = default;
};
#endif //TP_LOOPTYPE_H
