#include "../../../include/GameLogic/Soldiers/p90soldier.h"

P90Soldier::P90Soldier(int32_t x, int32_t y, int8_t dir, uint8_t health, unique_ptr<Weapon> &&weapon, unique_ptr<Grenade> &&grenade) :
    x(x),
    y(y),
    dir(dir),
    health(health),
    weapon(std::move(weapon)),
    grenade(std::move(grenade)) {
}

void P90Soldier::move(
    GameMap &map,
    uint8_t state,
    uint8_t moveAxis,
    int8_t moveDirection,
    uint8_t moveForce) {

    uint32_t next_x;
    uint32_t next_y;

    switch(moveAxis) {
        case X:
            next_x = x + (moveDirection * moveForce);
            next_y = y;
            break;
        case Y:
            next_y = y + (moveDirection * moveForce);
            next_x = x;
            break;
    }

    if ((next_x > map.get_x_limit()) || (next_y > map.get_y_limit())) return;

    std::unique_ptr<CollisionZone> &next_cz = map.getCollisionZone(next_x, next_y);
    if (next_cz->is_occupied()) return;
    std::unique_ptr<CollisionZone> &actual_cz = map.getCollisionZone(x, y);
    actual_cz->vacate();
    next_cz->occupy(this, nullptr);
    x = next_x;
    y = next_y;
}

void P90Soldier::shoot(GameMap &map, uint8_t state) {
    weapon->shoot(x, y, dir, std::ref(map));
}

void P90Soldier::reload(uint8_t state) {
    weapon->reload(state);
}

void P90Soldier::throwGrenade(GameMap &map) {
    grenade->throwg(x, y, dir, std::ref(map));
}

void P90Soldier::cGrenade(void) {
    // grenade_type = otra
}

void P90Soldier::recvDamage(uint8_t damage) {
    health -= damage;
}
