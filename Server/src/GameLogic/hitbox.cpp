#include "../../include/GameLogic/hitbox.h"

Hitbox::Hitbox(
    int16_t x_min,
    int16_t x_max,
    int16_t y_min,
    int16_t y_max) :
    x_min(x_min),
    x_max(x_max),
    y_min(y_min),
    y_max(y_max) {
}

void Hitbox::setValues(int16_t x_mi, int16_t x_ma, int16_t y_mi, int16_t y_ma) {
    x_min = x_mi;
    x_max = x_ma;
    y_min = y_mi;
    y_max = y_ma;
}

bool Hitbox::move_hits(Position &other_position) {
    int16_t x_max_other = other_position.getXMax();
    int16_t x_min_other = other_position.getXMin();
    int16_t y_max_other = other_position.getYMax();
    int16_t y_min_other = other_position.getYMin();

    bool hits_x = ((x_min <= x_max_other) && (x_max_other <= x_max)) || (((x_min <= x_min_other) && (x_min_other <= x_max)));

    bool hits_y = ((y_min <= y_max_other) && (y_max_other <= y_max)) || (((y_min <= y_min_other) && (y_min_other <= y_max)));

    return (hits_x && hits_y);
}

bool Hitbox::shoot_hits(Position &victim_position) {
    int16_t x_max_victim = victim_position.getXMax();
    int16_t x_min_victim = victim_position.getXMin();
    int16_t y_victim = victim_position.getYPos();

    bool hits_x = ((x_min <= x_max_victim) && (x_max_victim <= x_max)) || (((x_min <= x_min_victim) && (x_min_victim <= x_max)));

    bool hits_y = ((y_min <= y_victim) && (y_victim <= y_max));

    return (hits_x && hits_y);
}

int16_t Hitbox::getXMax(void) {
    return x_max;
}

int16_t Hitbox::getXMin(void) {
    return x_min;
}

int16_t Hitbox::getYMax(void) {
    return y_max;
}

int16_t Hitbox::getYMin(void) {
    return y_min;
}
