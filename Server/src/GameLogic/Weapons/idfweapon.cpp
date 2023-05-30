#include "../../../include/GameLogic/Weapons/idfweapon.h"

IdfWeapon::IdfWeapon(uint8_t ammo, uint8_t damage) :
    ammo(ammo),
    damage(damage) {
}

void IdfWeapon::shoot(uint32_t x, uint32_t y, uint8_t dir, GameMap &map) {
    if (ammo == 0) return;
    std::vector<std::unique_ptr<CollisionZone>> &trajectory = map.getCollisionZoneRow(y);
    uint32_t x_limit = map.get_x_limit();
    uint32_t damage = IDF_DAMAGE;
    // disparo hacia la izquierda
    if (dir == LEFT) {
        for (uint32_t i = x; i > 0; i--) {
            damage *= DAMAGE_REDUCTION_COEF;
            std::unique_ptr<CollisionZone> &cz = trajectory[i];
            if (cz->is_occupied()) {
                cz->executeCollision(damage);
                break;
            }
        }
    // disparo hacia la derecha
    } else {
        for (uint32_t i = x; i < x_limit; i++) {
            std::unique_ptr<CollisionZone> &cz = trajectory[i];
            damage *= DAMAGE_REDUCTION_COEF;
            if (cz->is_occupied()) {
                cz->executeCollision(damage);
                break;
            }
        }
    }
    ammo -= 1;
}

void IdfWeapon::reload(uint8_t state) {
    ammo = IDF_AMMO;
}
