#ifndef SOLDIERFACTORY_H_
#define SOLDIERFACTORY_H_

#include "../Soldiers/soldier.h"
#include "../Soldiers/scoutsoldier.h"
#include "../Soldiers/p90soldier.h"
#include "../Soldiers/idfsoldier.h"
#include "../Weapons/weaponfactory.h"
#include "../../../../Common/include/Information/information_code.h"

class SoldierFactory {
public:
    std::shared_ptr<Soldier> create(uint32_t soldier_id, uint8_t soldier_type);
    void load_values(const YAML::Node &node, 
    double *width, double *height, double *speed, double *health, uint8_t *grenade,
    double *revive_radius, double *revive_cooldown, double *reload_cooldown, double *thow_cooldown, double *throw_duration);
};

#endif  // SOLDIERFACTORY_H_
