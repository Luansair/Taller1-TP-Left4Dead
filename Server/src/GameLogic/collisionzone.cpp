#include "../../include/GameLogic/collisionzone.h"
#include "../../include/GameLogic/Soldiers/soldier.h"
#include "../../include/GameLogic/Zombies/zombie.h"

CollisionZone::CollisionZone(void) : 
    occupied(false) {
}

void CollisionZone::executeCollision(uint8_t damage) {
    soldier->recvDamage(damage);
}

bool CollisionZone::is_occupied(void) {
    return occupied;
}

void CollisionZone::occupy(Soldier* new_soldier, Zombie* new_zombie) {
    if (new_soldier) {
        soldier = new_soldier;
    } else {
        zombie = new_zombie;
    }
    occupied = true;
}

void CollisionZone::vacate(void) {
    soldier = nullptr;
    zombie = nullptr;
    occupied = false;
}