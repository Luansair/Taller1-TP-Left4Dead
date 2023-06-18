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
