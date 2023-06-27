#include "../../../include/GameLogic/Zombies/spear.h"
#include <random>

/* CONSTRUCTOR */

Spear::Spear(
    uint32_t zombie_id,
    double width,
    double height,
    double speed,
    double health,
    double sight,
    double listening_range,
    double hit_scope,
    double damage,
    double die_cooldown,
    double stunned_cooldown) :
    Zombie(zombie_id, width, height, speed, health, sight, listening_range, hit_scope, damage, die_cooldown, stunned_cooldown) {
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
