#ifndef HITBOX_H_
#define HITBOX_H_

#include "position.h"

#include <utility>
#include <cstdint>
#include <map>
#include <memory>

class Hitbox {
public:
    double x_min;
    double x_max;
    double y_min;
    double y_max;

    Hitbox() {}

    explicit Hitbox(double x_min, double x_max, double y_min, double y_max);
    void setValues(double x_min, double x_max, double y_min, double y_max);

    bool shoot_hits(const Position &victim_position);

    double getXMax(void);
    double getXMin(void);
    double getYMax(void);
    double getYMin(void);

};

#endif  // HITBOX_H_
