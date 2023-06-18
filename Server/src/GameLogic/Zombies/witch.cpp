#include "../../../include/GameLogic/Zombies/witch.h"
#include <random>

/* CONSTRUCTOR */

Witch::Witch(
    uint32_t zombie_id,
    double width,
    double height,
    double speed,
    double health) :
    Zombie(zombie_id, width, height, speed, health) {
}

uint8_t Witch::getZombieType(void) {
    return ZOMBIE;
}
