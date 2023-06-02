#include "../../include/GameLogic/collisionzone.h"
#include "../../include/GameLogic/Soldiers/soldier.h"
#include "../../include/GameLogic/Zombies/zombie.h"

CollisionZone::CollisionZone(uint32_t x, uint32_t y) : 
    x_pos(x),
    y_pos(y),
    occupied(false) {
}

void CollisionZone::executeCollision(int8_t damage) {
    soldier->recvDamage(damage);
}

bool CollisionZone::is_occupied(void) {
    return occupied;
}

bool CollisionZone::occupy(Soldier* new_soldier, Zombie* new_zombie, int8_t dir) {
    if (occupied) return false;
    if (new_soldier && new_zombie) return false;
    if (!(new_soldier || new_zombie)) return false;
    if (new_soldier) {
        soldier = new_soldier;
        soldier->setPos(x_pos, y_pos, dir);
    } else if (new_zombie) {
        zombie = new_zombie;
    }
    occupied = true;
    return true;
}

void CollisionZone::vacate(void) {
    soldier = nullptr;
    zombie = nullptr;
    occupied = false;
}

Soldier* CollisionZone::getSoldier(void) {
    return soldier;
}

Zombie* CollisionZone::getZombie(void) {
    return zombie;
}