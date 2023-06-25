#include "../../../include/GameLogic/Soldiers/p90soldier.h"

P90Soldier::P90Soldier(
    uint32_t soldier_id,
    double width,
    double height,
    double speed,
    double health,
    std::unique_ptr<Weapon>&& weapon,
    double revive_radius,
    uint8_t t_type,
    double revive_cooldown,
    double reload_cooldown,
    double throw_cooldown,
    double throw_duration) :
    Soldier(soldier_id, width, height, speed, health, std::move(weapon), t_type, revive_radius, revive_cooldown, reload_cooldown, throw_cooldown, throw_duration) {
}

uint8_t P90Soldier::getSoldierType(void) {
    return SOLDIER_P90;
}

// cambiar a soldier_2
uint8_t P90Soldier::getAction(void) {
    if (dying) return SOLDIER_2_DEAD;
    if (being_hurt) return SOLDIER_2_HURT;
    if (shooting) return SOLDIER_2_SHOOT_1;
    if (reloading) return SOLDIER_2_RECHARGE;
    if (moving) return SOLDIER_2_RUN;
    if (throwed) return SOLDIER_2_GRENADE;
    return SOLDIER_2_IDLE;
}
