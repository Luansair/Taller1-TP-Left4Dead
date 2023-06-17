#ifndef SPEAR_H_
#define SPEAR_H_

#include "zombie.h"

/* A pesar de que la mayoría de los infectados muestran un nivel cognitivo básico, algunos han llegado a
evolucionar a tal punto de ser capaces de usar armas como lanzas. */

class Spear : public Zombie {

public:
    explicit Spear(
    uint32_t zombie_id,
    int8_t dir,
    int8_t width,
    int8_t height,
    int8_t speed,
    int16_t health);

    uint8_t getZombieType(void) override;
};

#endif  // SPEAR_H_
