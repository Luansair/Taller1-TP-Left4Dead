#include "../../../include/GameLogic/Soldiers/scoutsoldier.h"

ScoutSoldier::ScoutSoldier(int32_t x, int32_t y, uint8_t health, unique_ptr<Weapon> &&weapon, unique_ptr<Grenade> &&grenade) :
    x(x),
    y(y),
    health(health),
    weapon(std::move(weapon)),
    grenade(std::move(grenade)) {
}

void ScoutSoldier::move(
    uint8_t state,
    uint8_t moveAxis,
    int8_t moveDirection,
    uint8_t moveForce) {
    
    // ver que hacer con state
    // habria que verificar que no se vaya de los limites
    // y que se superpongan posiciones
    switch(moveAxis)
    {
        case X:
            x += moveDirection * moveForce;
        case Y:
            y += moveDirection * moveForce;
    
    }
}

void ScoutSoldier::shoot(void) {
    weapon->shoot();
}

void ScoutSoldier::reload(void) {
    weapon->reload();
}

void ScoutSoldier::throwGrenade(void) {
    grenade->throwg();
}

void ScoutSoldier::cGrenade(void) {
    // grenade_type = otra
}
