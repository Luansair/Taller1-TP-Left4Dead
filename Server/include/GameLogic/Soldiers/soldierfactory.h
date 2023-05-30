#ifndef SOLDIERFACTORY_H_
#define SOLDIERFACTORY_H_

#include "../Soldiers/soldier.h"
#include "../Soldiers/scoutsoldier.h"
#include "../Soldiers/p90soldier.h"
#include "../Soldiers/idfsoldier.h"
#include "../Weapons/scoutweapon.h"
#include "../Weapons/p90weapon.h"
#include "../Weapons/idfweapon.h"

#define P90SOLDIER 1
#define SCOUTSOLDIER 2
#define IDFSOLDIER 3

#define P90SOLDIERHEALTH 100
#define IDFSOLDIERHEALTH 120
#define SCOUTSOLDIERHEALTH 80

#define P90_DAMAGE 50
#define P90_AMMO 30
#define SCOUT_DAMAGE 60
#define SCOUT_AMMO 20
#define IDF_DAMAGE 80
#define IDF_AMMO 50

class SoldierFactory {
public:
    std::unique_ptr<Soldier> create(uint8_t soldier_type);
};

#endif  // SOLDIERFACTORY_H_
