#include "../../../include/GameLogic/Grenades/smokegrenade.h"

SmokeGrenade::SmokeGrenade(uint8_t damage, uint8_t cooldown, uint8_t scope) :
    damage(damage),
    cooldown(cooldown),
    scope(scope) {
}

void SmokeGrenade::throwg(void) {
    // logica de explosion
}
