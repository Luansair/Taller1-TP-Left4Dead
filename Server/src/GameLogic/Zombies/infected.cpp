#include "../../../include/GameLogic/Zombies/infected.h"
#include <random>

/* CONSTRUCTOR */

Infected::Infected(
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

uint8_t Infected::getZombieType(void) {
    return ZOMBIE;
}

uint8_t Infected::getAction(void) {
    if (dying) return ZOMBIE_DEAD;
    if (being_hurt) return ZOMBIE_HURT;
    if (moving && stunned) return ZOMBIE_WALK;
    if (moving) return ZOMBIE_RUN;
    if (attacking) return ZOMBIE_ATTACK_1;
    return ZOMBIE_IDLE;
}

