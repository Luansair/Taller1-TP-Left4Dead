#include "../../../include/GameLogic/Zombies/venom.h"
#include <random>

/* CONSTRUCTOR */

Venom::Venom(
    uint32_t zombie_id,
    double width,
    double height,
    double speed,
    double health) :
    Zombie(zombie_id, width, height, speed, health) {
}

uint8_t Venom::getZombieType(void) {
    return VENOM;
}

uint8_t Venom::getAction(void) {
    if (dying) return VENOM_DEAD;
    if (being_hurt) return VENOM_HURT;
    if (moving) return VENOM_RUN;
    if (attacking) return VENOM_ATTACK_1;
    return VENOM_IDLE;
}
