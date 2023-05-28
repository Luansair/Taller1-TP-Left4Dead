#include "../../../include/GameLogic/Weapons/scoutweapon.h"

ScoutWeapon::ScoutWeapon(uint8_t ammo, uint8_t damage, uint8_t scope, uint8_t recoil) :
    ammo(ammo),
    damage(damage),
    scope(scope),
    recoil(recoil) {
}

void ScoutWeapon::shoot(void) {
    // logica de disparo
}

void ScoutWeapon::reload(void) {
    // logica de recarga
}
