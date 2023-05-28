#ifndef INFECTED_H_
#define INFECTED_H_

#include "zombie.h"

class Infected : public Zombie {
private:
    int32_t x;
    int32_t y;
    uint8_t health;

public:
    explicit Infected(int32_t x, int32_t y, uint8_t health);
};

#endif  // INFECTED_H_
