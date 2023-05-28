#ifndef WITCH_H_
#define WITCH_H_

#include "zombie.h"

class Witch: public Zombie {
private:
    int32_t x;
    int32_t y;
    uint8_t health;

public:
    explicit Witch(int32_t x, int32_t y, uint8_t health);
};

#endif  // WITCH_H_
