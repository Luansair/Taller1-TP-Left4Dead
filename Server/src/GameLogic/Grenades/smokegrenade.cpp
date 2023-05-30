#include "../../../include/GameLogic/Grenades/smokegrenade.h"

SmokeGrenade::SmokeGrenade(uint8_t damage, uint8_t cooldown, uint8_t scope) :
    damage(damage),
    cooldown(cooldown),
    scope(scope) {
}

void SmokeGrenade::throwg(uint32_t x, uint32_t y, uint8_t dir, GameMap &map) {
    // logica de explosion
}
