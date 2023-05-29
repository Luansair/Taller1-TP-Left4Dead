#include "../../../include/GameLogic/Weapons/p90weapon.h"

P90Weapon::P90Weapon(uint8_t ammo, uint8_t damage, uint8_t scope, uint8_t recoil) :
    ammo(ammo),
    damage(damage),
    scope(scope),
    recoil(recoil) {
}

void P90Weapon::shoot(uint32_t x, uint32_t y, uint8_t dir, GameMap &map) {
    // logica de disparo
}

void P90Weapon::reload(uint8_t state) {
    // logica de recarga
}
