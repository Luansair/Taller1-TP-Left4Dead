#ifndef INFECTED_H_
#define INFECTED_H_

#include "zombie.h"

/* Los infectados caminan o permanecen quietos en las calles si no son molestados pero la mayoría
empezará a caminar hacia los jugadores en cuanto estén a la vista para matarlos (sea a través de golpes,
zarpazos o mordidas). */

class Infected : public Zombie {
private:
    int32_t x;
    int32_t y;
    uint8_t health;

public:
    explicit Infected(int32_t x, int32_t y, uint8_t health);
};

#endif  // INFECTED_H_
