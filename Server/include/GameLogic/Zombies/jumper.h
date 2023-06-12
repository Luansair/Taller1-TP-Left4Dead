#ifndef JUMPER_H_
#define JUMPER_H_

#include "zombie.h"

/* Este infectado tiene la particularidad de saltar sobre sus víctimas y producirles daño al caer sobre ellas. El
jugador puede ver que el infectado está por saltar por su característica pose en el piso. Si es lo
suficientemente rápido de reflejos, podrá correr y evitar el ataque. */

class Jumper : public Zombie {
private:
    int32_t x;
    int32_t y;
    uint8_t health;

public:
    explicit Jumper(int32_t x, int32_t y, uint8_t health);
};

#endif  // JUMPER_H_
