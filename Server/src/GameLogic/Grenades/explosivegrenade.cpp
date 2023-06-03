#include "../../../include/GameLogic/Grenades/explosivegrenade.h"

ExplosiveGrenade::ExplosiveGrenade(uint8_t damage, uint8_t cooldown, uint8_t scope) :
    damage(damage),
    cooldown(cooldown),
    scope(scope) {
}

void ExplosiveGrenade::throwg(uint32_t x, uint32_t y, uint8_t dir) {
}
