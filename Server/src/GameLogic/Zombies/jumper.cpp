#include "../../../include/GameLogic/Zombies/jumper.h"
#include <random>

/* CONSTRUCTOR */

Jumper::Jumper(
    uint32_t zombie_id,
    double width,
    double height,
    double speed,
    double health) :
    Zombie(zombie_id, width, height, speed, health) {
}

uint8_t Jumper::getZombieType(void) {
    return ZOMBIE;
}