#include "../../../include/GameLogic/Zombies/spear.h"
#include <random>

/* CONSTRUCTOR */

Spear::Spear(
    uint32_t zombie_id,
    double width,
    double height,
    double speed,
    double health) :
    Zombie(zombie_id, width, height, speed, health) {
}

uint8_t Spear::getZombieType(void) {
    return ZOMBIE;
}