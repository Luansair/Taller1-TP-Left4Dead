#include "../../../include/GameLogic/Soldiers/soldier.h"

Soldier::Soldier(
    uint16_t x,
    uint16_t y,
    int8_t dir,
    uint8_t width,
    uint8_t height,
    uint8_t speed,
    uint16_t health,
    std::unique_ptr<Weapon>&& weapon,
    std::unique_ptr<Grenade>&& grenade) :
    x(x),
    y(y),
    dir(dir),
    width(width),
    height(height),
    speed(speed),
    health(health),
    weapon(std::move(weapon)),
    grenade(std::move(grenade)) {
}

void Soldier::move(
    uint8_t state,
    uint8_t moveAxis,
    int8_t moveDirection,
    uint8_t moveForce) {
    
    // int32_t next_x;
    // int32_t next_y;
    // int8_t next_dir;

    // switch(moveAxis) {
    //     case X:
    //         next_x = x + (moveDirection * moveForce);
    //         next_y = y;
    //         next_dir = moveDirection;
    //         break;
    //     case Y:
    //         next_y = y - (moveDirection * moveForce);
    //         next_x = x;
    //         next_dir = dir;
    //         break;
    // }

    // if ((next_x >= map.get_x_limit()) || (next_x < 0) || (next_y >= map.get_y_limit()) || (next_y < 0)) return;
}

void Soldier::shoot(uint8_t state) {
    weapon->shoot(x, y, dir);
}

void Soldier::reload(uint8_t state) {
    weapon->reload(state);
}

void Soldier::throwGrenade(void){
    grenade->throwg(x, y, dir);
}

void Soldier::cGrenade(void) {
    // grenade_type = otra
}

void Soldier::recvDamage(int8_t damage) {
    if (damage < health) {
        health -= damage; 
        return;
    }
}

void Soldier::setPos(uint16_t new_x, uint16_t new_y, int8_t new_dir) {
    x = new_x;
    y = new_y;
    dir = new_dir;
}

uint16_t Soldier::getXPos(void) {
    return x;
}
uint16_t Soldier::getYPos(void) {
    return y;
}

int8_t Soldier::getDir(void) {
    return dir;
}

int8_t Soldier::getHealth(void) {
    return health;
}
