#ifndef SPEAR_H_
#define SPEAR_H_

#include "zombie.h"

class Spear : public Zombie {
private:
    int32_t x;
    int32_t y;
    uint8_t health;

public:
    explicit Spear(int32_t x, int32_t y, uint8_t health);
};

#endif  // SPEAR_H_
