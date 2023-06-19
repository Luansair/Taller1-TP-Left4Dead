#include "../../../include/GameLogic/Zombies/infected.h"
#include <random>

/* CONSTRUCTOR */

Infected::Infected(
    uint32_t zombie_id,
    double width,
    double height,
    double speed,
    double health) :
    Zombie(zombie_id, width, height, speed, health) {
}

uint8_t Infected::getZombieType(void) {
    return ZOMBIE;
}
