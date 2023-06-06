#ifndef GRENADE_H_
#define GRENADE_H_

#include "../../../../Common/include/Information/information_code.h"

#include <cstdint>
#include <utility>

class Grenade {
public:
    virtual ~Grenade() {}
    virtual void throwg(uint32_t x, uint32_t y, uint8_t dir) = 0;
};

#endif  // GRENADE_H_
