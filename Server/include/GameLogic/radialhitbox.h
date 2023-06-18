#ifndef RADIALHITBOX_H_
#define RADIALHITBOX_H_

#include "position.h"

#include <utility>
#include <cstdint>
#include <map>
#include <memory>

class RadialHitbox {
public:
    double pi = 3.14159265358979;
    double x;
    double y;
    double radius;

    RadialHitbox() {}

    explicit RadialHitbox(double x, double y, double radius);
    void setValues(double x, double y, double radius);

    bool hits(const Position &victim_position);

};

#endif  // RADIALHITBOX_H_