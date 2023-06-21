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
    return WITCH;
}

uint8_t Witch::getAction(void) {
    if (dying) return WITCH_DEAD;
    if (being_hurt) return WITCH_HURT;
    if (moving) return WITCH_RUN;
    if (attacking) return WITCH_ATTACK_1;
    return WITCH_IDLE;
}
