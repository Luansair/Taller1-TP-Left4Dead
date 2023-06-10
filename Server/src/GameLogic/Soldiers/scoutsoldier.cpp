#include "../../../include/GameLogic/Soldiers/scoutsoldier.h"

ScoutSoldier::ScoutSoldier(
    uint32_t soldier_id,
    int8_t dir,
    int8_t width,
    int8_t height,
    int8_t speed,
    int16_t health,
    std::unique_ptr<Weapon>&& weapon,
    std::unique_ptr<Grenade>&& grenade) :
    Soldier(soldier_id, dir, width, height, speed, health, std::move(weapon), std::move(grenade)) {
}

uint8_t ScoutSoldier::getSoldierType(void) {
    return SOLDIER_2;
}