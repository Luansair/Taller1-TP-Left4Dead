#ifndef WEAPON_H_
#define WEAPON_H_

#include "../gamemap.h"
#include "../../../../Common/include/Action/action_code.h"

#include <utility>
#include <cstdint>

class Weapon {
public:
    virtual ~Weapon() {}
    virtual void shoot(uint32_t x, uint32_t y, uint8_t dir, GameMap &map) = 0;
    virtual void reload(uint8_t state) = 0;
};

#endif  // WEAPON_H_
