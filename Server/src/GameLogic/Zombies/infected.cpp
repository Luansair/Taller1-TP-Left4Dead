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

uint8_t Infected::getAction(void) {
    if (dying) return ZOMBIE_DEAD;
    if (being_hurt) return ZOMBIE_HURT;
    if (moving) return ZOMBIE_RUN;
    if (attacking) return ZOMBIE_ATTACK_1;
    return ZOMBIE_IDLE;
}

