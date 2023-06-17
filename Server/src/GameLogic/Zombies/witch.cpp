#include "../../../include/GameLogic/Zombies/witch.h"
#include <random>

/* CONSTRUCTOR */

Witch::Witch(
    uint32_t zombie_id,
    int8_t dir,
    int8_t width,
    int8_t height,
    int8_t speed,
    int16_t health) :
    Zombie(zombie_id, dir, width, height, speed, health) {
}

uint8_t Witch::getZombieType(void) {
    return ZOMBIE;
}
