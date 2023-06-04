#ifndef WEAPON_H_
#define WEAPON_H_

#include "../../../../Common/include/Action/action_code.h"
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
public:
    virtual ~Weapon() {}

    virtual bool shoot(
    Position& from,
    int8_t dir,
    uint16_t time,
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies) = 0;

    virtual void reload(void) = 0;
};

#endif  // WEAPON_H_
