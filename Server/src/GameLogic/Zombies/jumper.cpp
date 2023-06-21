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
    return JUMPER;
}

uint8_t Jumper::getAction(void) {
    if (dying) return JUMPER_DEAD;
    if (being_hurt) return JUMPER_HURT;
    if (moving) return JUMPER_RUN;
    if (attacking) return JUMPER_ATTACK_1;
    return JUMPER_IDLE;
}
