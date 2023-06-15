#ifndef SOLDIERFACTORY_H_
#define SOLDIERFACTORY_H_

#include "../Soldiers/soldier.h"
#include "../Soldiers/scoutsoldier.h"
#include "../Soldiers/p90soldier.h"
#include "../Soldiers/idfsoldier.h"
#include "../Weapons/weaponfactory.h"
#include "../Grenades/grenadefactory.h"

#define P90SOLDIER 1
#define SCOUTSOLDIER 2
#define IDFSOLDIER 3

#define P90SOLDIERHEALTH 100
#define P90SOLDIERWIDTH 2
#define P90SOLDIERHEIGTH 6
#define P90SOLDIERSPEED 1

#define IDFSOLDIERHEALTH 100
#define IDFSOLDIERWIDTH 2
#define IDFSOLDIERHEIGTH 6
#define IDFSOLDIERSPEED 1

#define SCOUTSOLDIERHEALTH 100
#define SCOUTSOLDIERWIDTH 2
#define SCOUTSOLDIERHEIGTH 6
#define SCOUTSOLDIERSPEED 1

class SoldierFactory {
public:
    std::shared_ptr<Soldier> create(uint32_t soldier_id, uint8_t soldier_type);
};

#endif  // SOLDIERFACTORY_H_
