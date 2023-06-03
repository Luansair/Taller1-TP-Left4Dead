#ifndef IDFSOLDIER_H_
#define IDFSOLDIER_H_

#include "soldier.h"

class IdfSoldier : public Soldier {

public:
    explicit IdfSoldier(
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

#endif  // IDFSOLDIER_H_
