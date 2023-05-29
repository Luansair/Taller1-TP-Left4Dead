#include "../../../include/GameLogic/Grenades/aerialgrenade.h"

AerialGrenade::AerialGrenade(uint8_t damage, uint8_t cooldown, uint8_t scope) :
    damage(damage),
    cooldown(cooldown),
    scope(scope) {
}

void AerialGrenade::throwg(GameMap &map) {
    // logica de explosion
}
