#include "../../../include/GameLogic/Soldiers/scoutsoldier.h"

ScoutSoldier::ScoutSoldier(
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

uint8_t ScoutSoldier::getSoldierType(void) {
    return SOLDIER_SCOUT;
}

// cambiar a soldier_3
uint8_t ScoutSoldier::getAction(void) {
    if (dying) return SOLDIER_3_DEAD;
    if (being_hurt) return SOLDIER_3_HURT;
    if (shooting) return SOLDIER_3_SHOOT_1;
    if (reloading) return SOLDIER_3_RECHARGE;
    if (moving) return SOLDIER_3_RUN;
    if (throwed) return SOLDIER_3_GRENADE;
    return SOLDIER_3_IDLE;
}