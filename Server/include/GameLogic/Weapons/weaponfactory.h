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

#define P90_DAMAGE 50
#define P90_AMMO 30
#define P90_SCOPE 2
#define SCOUT_DAMAGE 60
#define SCOUT_AMMO 20
#define SCOUT_SCOPE 2
#define IDF_DAMAGE 80
#define IDF_AMMO 50
#define IDF_SCOPE 2

class WeaponFactory {
public:
    std::unique_ptr<Weapon> create(uint8_t weapon_type);
};

#endif  // WEAPONFACTORY_H_
