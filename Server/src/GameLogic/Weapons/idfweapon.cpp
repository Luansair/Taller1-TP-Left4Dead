#include "../../../include/GameLogic/Weapons/idfweapon.h"

IdfWeapon::IdfWeapon(uint8_t ammo, uint8_t damage, uint8_t scope, uint8_t recoil) :
    ammo(ammo),
    damage(damage),
    scope(scope),
    recoil(recoil) {
}

void IdfWeapon::shoot(void) {
    // logica de disparo
}

void IdfWeapon::reload(void) {
    // logica de recarga
}
