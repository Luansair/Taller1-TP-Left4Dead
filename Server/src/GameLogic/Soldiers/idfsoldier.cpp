#include "../../../include/GameLogic/Soldiers/idfsoldier.h"

IdfSoldier::IdfSoldier(
    uint32_t soldier_id,
    double width,
    double height,
    double speed,
    double health,
    std::unique_ptr<Weapon>&& weapon,
    std::unique_ptr<Grenade>&& grenade) :
    Soldier(soldier_id, width, height, speed, health, std::move(weapon), std::move(grenade)) {
}

uint8_t IdfSoldier::getSoldierType(void) {
    return SOLDIER_IDF;
}

uint8_t IdfSoldier::getAction(void) {
    if (dying) return SOLDIER_1_DEAD;
    if (being_hurt) return SOLDIER_1_HURT;
    if (shooting) return SOLDIER_1_SHOOT_1;
    if (reloading) return SOLDIER_1_RECHARGE;
    if (moving) return SOLDIER_1_RUN;
    if (throwing) return SOLDIER_1_GRENADE;
    return SOLDIER_1_IDLE;
}
