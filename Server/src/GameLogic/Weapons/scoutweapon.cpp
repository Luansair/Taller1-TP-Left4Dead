#include "../../../include/GameLogic/Weapons/scoutweapon.h"

ScoutWeapon::ScoutWeapon(uint8_t ammo, uint8_t damage) :
    ammo(ammo),
    damage(damage) {
}

void ScoutWeapon::shoot(int32_t x, int32_t y, int8_t dir, GameMap &map) {
    if (ammo == 0) return;
    std::vector<std::unique_ptr<CollisionZone>> &trajectory = map.getCollisionZoneRow(y);
    int32_t x_limit = map.get_x_limit();
    uint8_t shoot_damage = damage;
    // disparo hacia la izquierda
    if (dir == LEFT) {
        for (int32_t i = x-1; i > -1; i--) {
            std::unique_ptr<CollisionZone> &cz = trajectory[i];
            if (cz->is_occupied()) {
                cz->executeCollision(shoot_damage);
                shoot_damage *= DAMAGE_REDUCTION_COEF;
            }
        }
    // disparo hacia la derecha
    } else {
        for (int32_t i = x+1; i < x_limit; i++) {
            std::unique_ptr<CollisionZone> &cz = trajectory[i];
            if (cz->is_occupied()) {
                cz->executeCollision(shoot_damage);
                shoot_damage *= DAMAGE_REDUCTION_COEF;
            }
        }
    }
    ammo -= 1;
}

void ScoutWeapon::reload(uint8_t state) {
    ammo = SCOUT_AMMO;
}
