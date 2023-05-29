#include "../../include/GameLogic/collisionzone.h"

CollisionZone::CollisionZone(void) : 
    occupied(false) {
}

void CollisionZone::executeCollision(uint8_t damage) {
    // occupant->receive_damage(damage);
}

bool CollisionZone::is_occupied(void) {
    return occupied;
}

void CollisionZone::occupy(Soldier* new_soldier) {
    soldier = new_soldier;
}

void CollisionZone::vacate(void) {
    soldier = nullptr;
    occupied = false;
}