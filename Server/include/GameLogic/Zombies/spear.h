#ifndef SPEAR_H_
#define SPEAR_H_

#include "zombie.h"

/* A pesar de que la mayoría de los infectados muestran un nivel cognitivo básico, algunos han llegado a
evolucionar a tal punto de ser capaces de usar armas como lanzas. */

class Spear : public Zombie {
public:
    explicit Spear(int32_t x, int32_t y, uint8_t health);
};

#endif  // SPEAR_H_
