#ifndef SCOUTSOLDIER_H_
#define SCOUTSOLDIER_H_

#include "soldier.h"

class ScoutSoldier : public Soldier {

public:
    explicit ScoutSoldier(
    uint16_t x, 
    uint16_t y,
    int8_t dir,
    uint8_t width,
    uint8_t height,
    uint8_t speed,
    uint16_t health,
    std::unique_ptr<Weapon>&& weapon,
    std::unique_ptr<Grenade>&& grenade);

};

#endif  // SCOUTSOLDIER_H_
