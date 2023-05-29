#include "../../../include/GameLogic/Weapons/p90weapon.h"

P90Weapon::P90Weapon(uint8_t ammo, uint8_t damage, uint8_t scope, uint8_t recoil) :
    ammo(ammo),
    damage(damage),
    scope(scope),
    recoil(recoil) {
}

void P90Weapon::shoot(uint32_t x, uint32_t y, uint8_t dir, GameMap &map) {
    if (ammo == 0) return;
    vector<unique_ptr<CollisionZone>> &trajectory = map.getCollisionZoneRow(y);
    uint32_t x_limit = map.get_x_limit();
    uint32_t damage = P90_DAMAGE;
    // disparo hacia la izquierda
    if (dir == LEFT) {
        for (uint32_t i = x; i > 0; i--) {
            unique_ptr<CollisionZone> &cz = trajectory[i];
            if (cz->is_occupied()) {
                cz->executeCollision(damage);
                break;
            }
        }
    // disparo hacia la derecha
    } else {
        for (uint32_t i = x; i < x_limit; i++) {
            unique_ptr<CollisionZone> &cz = trajectory[i];
            if (cz->is_occupied()) {
                cz->executeCollision(damage);
                break;
            }
        }
    }
    ammo -= 1;
}

void P90Weapon::reload(uint8_t state) {
    ammo = P90_AMMO;
}
