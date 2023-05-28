#include "../../../include/GameLogic/Grenades/explosivegrenade.h"

ExplosiveGrenade::ExplosiveGrenade(uint8_t damage, uint8_t cooldown, uint8_t scope) :
    damage(damage),
    cooldown(cooldown),
    scope(scope) {
}

void ExplosiveGrenade::throwg(void) {
    // logica de explosion
}
