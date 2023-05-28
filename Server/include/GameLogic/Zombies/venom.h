#ifndef VENOM_H_
#define VENOM_H_

#include "zombie.h"

class Venom : public Zombie {
private:
    int32_t x;
    int32_t y;
    uint8_t health;

public:
    explicit Venom(int32_t x, int32_t y, uint8_t health);
};

#endif  // VENOM_H_
