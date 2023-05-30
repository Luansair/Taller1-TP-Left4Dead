#include "../../../include/GameLogic/Grenades/explosivegrenade.h"

ExplosiveGrenade::ExplosiveGrenade(uint8_t damage, uint8_t cooldown, uint8_t scope) :
    damage(damage),
    cooldown(cooldown),
    scope(scope) {
}

void ExplosiveGrenade::throwg(uint32_t x, uint32_t y, uint8_t dir, GameMap &map) {
    if (cooldown > 0) return;
    uint32_t x_explosion;
    // tiro hacia la izquierda
    if (dir == LEFT) {
        x_explosion = x - scope;
    // tiro hacia la derecha
    } else {
        x_explosion = x + scope;
    }
    // zona de explosion
    for (int32_t i = -4; i < 5; i++) {
        for (int32_t j = -4; j < 5; j++) {
            unique_ptr<CollisionZone> &cz = map.getCollisionZone(x_explosion + i, y + j);
            if (cz->is_occupied()) {
                cz->executeCollision(damage);
            }
            
        }
    }
}
