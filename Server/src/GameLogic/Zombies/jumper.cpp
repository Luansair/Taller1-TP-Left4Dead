#include "../../../include/GameLogic/Zombies/jumper.h"
#include <random>

/* CONSTRUCTOR */

Jumper::Jumper(
    uint32_t zombie_id,
    int8_t dir,
    int8_t width,
    int8_t height,
    int8_t speed,
    int16_t health) :
    Zombie(zombie_id, dir, width, height, speed, health) {
}

uint8_t Jumper::getZombieType(void) {
    return ZOMBIE;
}