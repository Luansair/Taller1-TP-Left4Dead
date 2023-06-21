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
    return SPEAR;
}

uint8_t Spear::getAction(void) {
    if (dying) return SPEAR_DEAD;
    if (being_hurt) return SPEAR_HURT;
    if (moving) return SPEAR_RUN;
    if (attacking) return SPEAR_ATTACK_1;
    return SPEAR_IDLE;
}
