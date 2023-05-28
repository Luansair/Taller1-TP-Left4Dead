#ifndef JUMPER_H_
#define JUMPER_H_

#include "zombie.h"

class Jumper : public Zombie {
private:
    int32_t x;
    int32_t y;
    uint8_t health;

public:
    explicit Jumper(int32_t x, int32_t y, uint8_t health);
};

#endif  // JUMPER_H_
