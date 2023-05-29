#include "../../../include/GameLogic/Weapons/scoutweapon.h"

ScoutWeapon::ScoutWeapon(uint8_t ammo, uint8_t damage, uint8_t scope, uint8_t recoil) :
    ammo(ammo),
    damage(damage),
    scope(scope),
    recoil(recoil) {
}

void ScoutWeapon::shoot(uint32_t x, uint32_t y, uint8_t dir, GameMap &map) {
    vector<unique_ptr<CollisionZone>> &trajectory = map.getCollisionZoneRow(x);
    uint32_t y_limit = map.get_y_limit();
    uint8_t damage = SCOUT_DAMAGE;
    if (dir == LEFT) {
        for (uint32_t i = y; i > 0; i--) {
            unique_ptr<CollisionZone> &cz = trajectory[i];
            cz->executeCollision(damage);
            damage *= DAMAGE_REDUCTION_COEF;
        }
    } else {
        for (uint32_t i = y; i < y_limit; i++) {
            unique_ptr<CollisionZone> &cz = trajectory[i];
            cz->executeCollision(damage);
            damage *= DAMAGE_REDUCTION_COEF;
        }
    }
}

void ScoutWeapon::reload(uint8_t state) {
    // logica de recarga
}
