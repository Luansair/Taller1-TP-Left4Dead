#ifndef GRENADEFACTORY_H_
#define GRENADEFACTORY_H_

#include "grenade.h"
#include "explosivegrenade.h"
#include "smokegrenade.h"
#include "aerialgrenade.h"

#include <memory>

#define EXPLOSIVE 1
#define SMOKE 2
#define AERIAL 3

#define EXPLOSIVE_DAMAGE 50
#define EXPLOSIVE_COOLDOWN 50
#define EXPLOSIVE_SCOPE 30
#define SMOKE_DAMAGE 0
#define SMOKE_COOLDOWN 50
#define SMOKE_SCOPE 30
#define AERIAL_DAMAGE 50
#define AERIAL_COOLDOWN 50
#define AERIAL_SCOPE 30

class GrenadeFactory {
public:
    std::unique_ptr<Grenade> create(uint8_t grenade_type);
};

#endif  // GRENADEFACTORY_H_
