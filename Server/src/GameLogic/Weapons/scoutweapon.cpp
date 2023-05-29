#include "../../../include/GameLogic/Weapons/scoutweapon.h"

ScoutWeapon::ScoutWeapon(uint8_t ammo, uint8_t damage, uint8_t scope, uint8_t recoil) :
    ammo(ammo),
    damage(damage),
    scope(scope),
    recoil(recoil) {
}

void ScoutWeapon::shoot(uint32_t x, uint32_t y, uint8_t dir, GameMap &map) {
    if (ammo == 0) return;
    vector<unique_ptr<CollisionZone>> &trajectory = map.getCollisionZoneRow(y);
    uint32_t x_limit = map.get_x_limit();
    uint8_t damage = SCOUT_DAMAGE;
    // disparo hacia la izquierda
    if (dir == LEFT) {
        for (uint32_t i = x; i > 0; i--) {
            unique_ptr<CollisionZone> &cz = trajectory[i];
            if (cz->is_occupied()) {
                cz->executeCollision(damage);
                damage *= DAMAGE_REDUCTION_COEF;
            }
        }
    // disparo hacia la derecha
    } else {
        for (uint32_t i = x; i < x_limit; i++) {
            unique_ptr<CollisionZone> &cz = trajectory[i];
            if (cz->is_occupied()) {
                cz->executeCollision(damage);
                damage *= DAMAGE_REDUCTION_COEF;
            }
        }
    }
    ammo -= 1;
}

void ScoutWeapon::reload(uint8_t state) {
    ammo = SCOUT_AMMO;
}
