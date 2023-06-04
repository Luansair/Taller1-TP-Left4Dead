#ifndef HITBOX_H_
#define HITBOX_H_

#include "position.h"

#include <utility>
#include <cstdint>
#include <map>
#include <memory>

class Hitbox {
public:
    uint16_t x_min;
    uint16_t x_max;
    uint8_t y_min;
    uint8_t y_max;

    explicit Hitbox(uint16_t x_min, uint16_t x_max, uint16_t y_min, uint16_t y_max);

    bool hits(Position &victim_position);

    uint16_t getXMax(void);
    uint16_t getXMin(void);
    uint16_t getYMax(void);
    uint16_t getYMin(void);

};

#endif  // HITBOX_H_
