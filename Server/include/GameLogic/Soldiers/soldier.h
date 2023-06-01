#ifndef SOLDIER_H_
#define SOLDIER_H_

#include "../collisionzone.h"
#include "../Weapons/weapon.h"
#include "../Grenades/grenade.h"
#include "../Grenades/explosivegrenade.h"
#include "../Grenades/smokegrenade.h"
#include "../Grenades/aerialgrenade.h"
#include "../../../../Common/include/Action/action_code.h"
#include "../gamemap.h"

#include <memory>

class Soldier {
public:
    virtual ~Soldier() {}

    virtual void move(GameMap &map,
    uint8_t state,
    uint8_t moveAxis,
    int8_t moveDirection,
    uint8_t moveForce) = 0;

    virtual void shoot(GameMap &map, uint8_t state) = 0;

    virtual void reload(uint8_t state) = 0;

    virtual void throwGrenade(GameMap &map) = 0;

    virtual void cGrenade(void) = 0;

    virtual void recvDamage(uint8_t damage) = 0;

    virtual void setPos(uint32_t x, uint32_t y) = 0;
};

#endif  // SOLDIER_H_
