#ifndef GRENADE_H_
#define GRENADE_H_

#include "../gamemap.h"

#include <cstdint>
#include <utility>

class Grenade {
public:
    virtual ~Grenade() {}
    virtual void throwg(GameMap &map) = 0;
};

#endif  // GRENADE_H_
