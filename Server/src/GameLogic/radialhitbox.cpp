#include "../../include/GameLogic/radialhitbox.h"
#include<cmath>

RadialHitbox::RadialHitbox(
    double x,
    double y,
    double radius) :
    x(x),
    y(y),
    radius(radius) {
}

void RadialHitbox::setValues(double new_x, double new_y, double new_radius) {
    x = new_x;
    y = new_y;
    radius = new_radius;
}

bool RadialHitbox::hits(const Position &victim_position) {
    double other_x = victim_position.getXPos();
    double other_y = victim_position.getYPos();

    double distance = std::sqrt(std::pow(std::abs(x - other_x), 2) + std::pow(std::abs(y - other_y), 2));
    return (distance <= radius);
}
