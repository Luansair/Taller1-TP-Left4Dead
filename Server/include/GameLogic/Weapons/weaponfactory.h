#ifndef WEAPONFACTORY_H_
#define WEAPONFACTORY_H_

#include "weapon.h"
#include "scoutweapon.h"
#include "p90weapon.h"
#include "idfweapon.h"
#include "../../../../Common/include/Information/information_code.h"

#include <memory>
#include "yaml-cpp/yaml.h"

class WeaponFactory {
public:
    std::unique_ptr<Weapon> create(uint32_t soldier_id, uint8_t weapon_type);
    void load_values(const YAML::Node &node, uint16_t *ammo, double *damage, double *scope, double *reduction);
};

#endif  // WEAPONFACTORY_H_
