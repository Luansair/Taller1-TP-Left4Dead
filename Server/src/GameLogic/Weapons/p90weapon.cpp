#include "../../../include/GameLogic/Weapons/p90weapon.h"

P90Weapon::P90Weapon(uint8_t ammo, uint8_t damage, uint8_t scope, uint8_t recoil) :
    ammo(ammo),
    damage(damage),
    scope(scope),
    recoil(recoil) {
}

void P90Weapon::shoot(void) {
    // logica de disparo
}

void P90Weapon::reload(void) {
    // logica de recarga
}
