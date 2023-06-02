#include "../../../include/GameLogic/Soldiers/scoutsoldier.h"

ScoutSoldier::ScoutSoldier(int8_t health, std::unique_ptr<Weapon> &&weapon, std::unique_ptr<Grenade> &&grenade) :
    x(0),
    y(0),
    dir(0),
    health(health),
    weapon(std::move(weapon)),
    grenade(std::move(grenade)) {
}

void ScoutSoldier::move(
    GameMap &map,
    uint8_t state,
    uint8_t moveAxis,
    int8_t moveDirection,
    uint8_t moveForce) {
    
    int32_t next_x;
    int32_t next_y;
    int8_t next_dir;

    switch(moveAxis) {
        case X:
            next_x = x + (moveDirection * moveForce);
            next_y = y;
            next_dir = moveDirection;
            break;
        case Y:
            next_y = y - (moveDirection * moveForce);
            next_x = x;
            next_dir = dir;
            break;
    }

    if ((next_x >= map.get_x_limit()) || (next_x < 0) || (next_y >= map.get_y_limit()) || (next_y < 0)) return;

    std::unique_ptr<CollisionZone> &actual_cz = map.getCollisionZone(x, y);
    std::unique_ptr<CollisionZone> &next_cz = map.getCollisionZone(next_x, next_y);
    if (!(next_cz->occupy(this, nullptr, next_dir))) return;
    actual_cz->vacate();
}

void ScoutSoldier::shoot(GameMap &map, uint8_t state) {
    weapon->shoot(x, y, dir, std::ref(map));
}

void ScoutSoldier::reload(uint8_t state) {
    weapon->reload(state);
}

void ScoutSoldier::throwGrenade(GameMap &map) {
    grenade->throwg(x, y, dir, std::ref(map));
}

void ScoutSoldier::cGrenade(void) {
    // grenade_type = otra
}

void ScoutSoldier::recvDamage(int8_t damage) {
    health -= damage; // chequeo de muerte hacer
}

void ScoutSoldier::setPos(int32_t new_x, int32_t new_y, int8_t new_dir) {
    x = new_x;
    y = new_y;
    dir = new_dir;
}

int32_t ScoutSoldier::getXPos(void) {
    return x;
}
int32_t ScoutSoldier::getYPos(void) {
    return y;
}

int8_t ScoutSoldier::getDir(void) {
    return dir;
}

int8_t ScoutSoldier::getHealth(void) {
    return health;
}
