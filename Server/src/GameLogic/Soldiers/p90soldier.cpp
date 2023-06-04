#include "../../../include/GameLogic/Soldiers/p90soldier.h"

P90Soldier::P90Soldier(
    int8_t dir,
    int8_t width,
    int8_t height,
    int8_t speed,
    int16_t health,
    std::unique_ptr<Weapon>&& weapon,
    std::unique_ptr<Grenade>&& grenade) :
    Soldier(dir, width, height, speed, health, std::move(weapon), std::move(grenade)) {
}
