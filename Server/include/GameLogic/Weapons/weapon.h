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
    int32_t dim_x,
    uint16_t time,
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies) = 0;

    virtual void reload() = 0;

    Weapon(const Weapon&) = delete;
    Weapon& operator=(const Weapon&) = delete;
};

#endif  // WEAPON_H_
