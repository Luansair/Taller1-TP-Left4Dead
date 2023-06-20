#ifndef WEAPON_H_
#define WEAPON_H_

#include "../../../../Common/include/Information/information_code.h"
#include "../../../include/GameLogic/position.h"
#include "../../../include/GameLogic/hitbox.h"

#include <utility>
#include <cstdint>
#include <cstdlib>
#include <map>
#include <memory>
#include <chrono>

class Soldier;
class Zombie;

class Weapon {
protected:
    Weapon() = default;
public:
    virtual ~Weapon() = default;

    virtual bool shoot(
    Position& from,
    int8_t dir,
    double dim_x,
    double time,
    std::chrono::_V2::steady_clock::time_point real_time,
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies) = 0;

    virtual void reload() = 0;

    Weapon(const Weapon&) = delete;
    Weapon& operator=(const Weapon&) = delete;
};

#endif  // WEAPON_H_
