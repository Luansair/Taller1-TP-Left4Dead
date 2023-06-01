#include "../../../include/GameLogic/Soldiers/idfsoldier.h"

IdfSoldier::IdfSoldier(uint8_t health, std::unique_ptr<Weapon> &&weapon, std::unique_ptr<Grenade> &&grenade) :
    x(0),
    y(0),
    dir(0),
    health(health),
    weapon(std::move(weapon)),
    grenade(std::move(grenade)) {
}

void IdfSoldier::move(
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
    if (!(next_cz->occupy(this, nullptr))) return;
    std::unique_ptr<CollisionZone> &actual_cz = map.getCollisionZone(x, y);
    actual_cz->vacate();
    x = next_x;
    y = next_y;
}

void IdfSoldier::shoot(GameMap &map, uint8_t state) {
    weapon->shoot(x, y, dir, std::ref(map));
}

void IdfSoldier::reload(uint8_t state) {
    weapon->reload(state);
}

void IdfSoldier::throwGrenade(GameMap &map) {
    grenade->throwg(x, y, dir, std::ref(map));
}

void IdfSoldier::cGrenade(void) {
    // grenade_type = otra
}

void IdfSoldier::recvDamage(uint8_t damage) {
    health -= damage;
}

void IdfSoldier::setPos(uint32_t new_x, uint32_t new_y) {
    x = new_x;
    y = new_y;
}

int32_t IdfSoldier::getXPos(void) {
    return x;
}
int32_t IdfSoldier::getYPos(void) {
    return y;
}
