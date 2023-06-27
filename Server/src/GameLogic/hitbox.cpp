#include "../../include/GameLogic/hitbox.h"

Hitbox::Hitbox(
    double x_min,
    double x_max,
    double y_min,
    double y_max) :
    x_min(x_min),
    x_max(x_max),
    y_min(y_min),
    y_max(y_max) {
}

void Hitbox::setValues(double x_mi, double x_ma, double y_mi, double y_ma) {
    x_min = x_mi;
    x_max = x_ma;
    y_min = y_mi;
    y_max = y_ma;
}

bool Hitbox::shoot_hits(const Position &victim_position) {
    double x_victim = victim_position.getXPos();
    double y_victim = victim_position.getYPos();

    bool hits_x = ((x_min <= x_victim) && (x_victim <= x_max));

    bool hits_y = ((y_min <= y_victim) && (y_victim <= y_max));

    return (hits_x && hits_y);
}

double Hitbox::getXMax(void) {
    return x_max;
}

double Hitbox::getXMin(void) {
    return x_min;
}

double Hitbox::getYMax(void) {
    return y_max;
}

double Hitbox::getYMin(void) {
    return y_min;
}
