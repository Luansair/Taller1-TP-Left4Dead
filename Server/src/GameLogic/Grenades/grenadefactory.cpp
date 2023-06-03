#include "../../../include/GameLogic/Grenades/grenadefactory.h"

std::unique_ptr<Grenade> GrenadeFactory::create(uint8_t grenade_type) {
    switch(grenade_type) {
        case EXPLOSIVE: {
            return std::unique_ptr<Grenade> (new ExplosiveGrenade(EXPLOSIVE_DAMAGE, EXPLOSIVE_COOLDOWN, EXPLOSIVE_SCOPE));
        }
        case SMOKE: {
            return std::unique_ptr<Grenade> (new SmokeGrenade(SMOKE_DAMAGE, SMOKE_COOLDOWN, SMOKE_SCOPE));
        }
        case AERIAL: {
            return std::unique_ptr<Grenade> (new AerialGrenade(AERIAL_DAMAGE, AERIAL_COOLDOWN, AERIAL_SCOPE));
        }
    }
    return std::unique_ptr<Grenade>(nullptr);
}
