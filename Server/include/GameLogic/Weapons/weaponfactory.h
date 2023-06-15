#ifndef WEAPONFACTORY_H_
#define WEAPONFACTORY_H_

#include "weapon.h"
#include "scoutweapon.h"
#include "p90weapon.h"
#include "idfweapon.h"

#include <memory>

#define P90WEAPON 1
#define SCOUTWEAPON 2
#define IDFWEAPON 3

class WeaponFactory {
public:
    std::unique_ptr<Weapon> create(uint8_t weapon_type);
};

#endif  // WEAPONFACTORY_H_
