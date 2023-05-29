#include "../../../include/GameLogic/Weapons/idfweapon.h"

IdfWeapon::IdfWeapon(uint8_t ammo, uint8_t damage, uint8_t scope, uint8_t recoil) :
    ammo(ammo),
    damage(damage),
    scope(scope),
    recoil(recoil) {
}

void IdfWeapon::shoot(uint32_t x, uint32_t y, uint8_t dir, GameMap &map) {
    // logica de disparo
}

void IdfWeapon::reload(uint8_t state) {
    // logica de recarga
}
