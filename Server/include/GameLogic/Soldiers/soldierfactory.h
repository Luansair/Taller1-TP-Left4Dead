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

class SoldierFactory {
public:
    std::shared_ptr<Soldier> create(uint32_t soldier_id, uint8_t soldier_type);
};

#endif  // SOLDIERFACTORY_H_
