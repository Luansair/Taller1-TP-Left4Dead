#ifndef SOLDIER_H_
#define SOLDIER_H_

#include <memory>
#include "../Weapons/scoutweapon.h"
#include "../Weapons/p90weapon.h"
#include "../Weapons/idfweapon.h"
#include "../Grenades/explosivegrenade.h"
#include "../Grenades/smokegrenade.h"
#include "../Grenades/aerialgrenade.h"
#include "../../../../Common/include/Action/action_code.h"
using namespace std;

class Soldier {
public:
    virtual ~Soldier() {}

    virtual void move(uint8_t state,
    uint8_t moveAxis,
    int8_t moveDirection,
    uint8_t moveForce) = 0;

    virtual void shoot(void) = 0;

    virtual void reload(void) = 0;

    virtual void throwGrenade(void) = 0;

    virtual void cGrenade(void) = 0;
};

#endif  // SOLDIER_H_
