#include "../../../include/GameLogic/Soldiers/scoutsoldier.h"

ScoutSoldier::ScoutSoldier(
    uint32_t soldier_id,
    double width,
    double height,
    double speed,
    double health,
    std::unique_ptr<Weapon>&& weapon,
    std::unique_ptr<Grenade>&& grenade) :
    Soldier(soldier_id, width, height, speed, health, std::move(weapon), std::move(grenade)) {
}

uint8_t ScoutSoldier::getSoldierType(void) {
    return SOLDIER_3;
}

// cambiar a soldier_3
uint8_t ScoutSoldier::getAction(void) {
    if (dying) return SOLDIER_1_DEAD;
    if (shooting) return SOLDIER_1_SHOOT_1;
    if (moving) return SOLDIER_1_RUN;
    if (reloading) return SOLDIER_1_RECHARGE;
    if (throwing) return SOLDIER_1_GRENADE_EXPLOSION;
    return SOLDIER_1_IDLE;
}