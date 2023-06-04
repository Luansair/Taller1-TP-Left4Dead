#include "../../include/GameLogic/hitbox.h"

Hitbox::Hitbox(
    uint16_t x_min,
    uint16_t x_max,
    uint16_t y_min,
    uint16_t y_max) :
    x_min(x_min),
    x_max(x_max),
    y_min(y_min),
    y_max(y_max) {
}

bool Hitbox::hits(Position &victim_position) {
    uint16_t x_max_victim = victim_position.getXMax();
    uint16_t x_min_victim = victim_position.getXMin();
    uint16_t y_max_victim = victim_position.getYMax();
    uint16_t y_min_victim = victim_position.getYMin();

    if ((((x_min_victim <= x_max) || (x_max <= x_max_victim)) || (((x_min_victim <= x_min) || (x_min <= x_max_victim)))) && 
    (((y_min_victim <= y_max) || (y_max <= y_max_victim)) || (((y_min_victim <= y_min) || (y_min <= y_max_victim))))) return true;

    return false;
}

uint16_t Hitbox::getXMax(void) {
    return x_max;
}

uint16_t Hitbox::getXMin(void) {
    return x_min;
}

uint16_t Hitbox::getYMax(void) {
    return y_max;
}

uint16_t Hitbox::getYMin(void) {
    return y_min;
}
