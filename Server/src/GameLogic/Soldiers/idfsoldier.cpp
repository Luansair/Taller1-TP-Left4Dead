#include "../../../include/GameLogic/Soldiers/idfsoldier.h"

IdfSoldier::IdfSoldier(int32_t x, int32_t y, uint8_t health, unique_ptr<Weapon> &&weapon, unique_ptr<Grenade> &&grenade) :
    x(x),
    y(y),
    health(health),
    weapon(std::move(weapon)),
    grenade(std::move(grenade)) {
}

void IdfSoldier::move(
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

void IdfSoldier::shoot(void) {
    weapon->shoot();
}

void IdfSoldier::reload(void) {
    weapon->reload();
}

void IdfSoldier::throwGrenade(void) {
    grenade->throwg();
}

void IdfSoldier::cGrenade(void) {
    // grenade_type = otra
}
