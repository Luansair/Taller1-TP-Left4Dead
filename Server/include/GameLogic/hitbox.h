#ifndef HITBOX_H_
#define HITBOX_H_

#include "position.h"

#include <utility>
#include <cstdint>
#include <map>
#include <memory>

class Hitbox {
public:
    int16_t x_min;
    int16_t x_max;
    int16_t y_min;
    int16_t y_max;

    Hitbox() {}

    explicit Hitbox(int16_t x_min, int16_t x_max, int16_t y_min, int16_t y_max);
    void setValues(int16_t x_min, int16_t x_max, int16_t y_min, int16_t y_max);

    bool move_hits(Position &victim_position);
    bool shoot_hits(Position &victim_position);

    int16_t getXMax(void);
    int16_t getXMin(void);
    int16_t getYMax(void);
    int16_t getYMin(void);

};

#endif  // HITBOX_H_
