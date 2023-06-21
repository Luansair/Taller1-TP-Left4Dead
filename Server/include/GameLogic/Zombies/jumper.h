#ifndef JUMPER_H_
#define JUMPER_H_

#include "zombie.h"

/* Este infectado tiene la particularidad de saltar sobre sus víctimas y producirles daño al caer sobre ellas. El
jugador puede ver que el infectado está por saltar por su característica pose en el piso. Si es lo
suficientemente rápido de reflejos, podrá correr y evitar el ataque. */

class Jumper : public Zombie {

public:
    explicit Jumper(
    uint32_t zombie_id,
    double width,
    double height,
    double speed,
    double health);

    uint8_t getZombieType(void) override;
    uint8_t getAction(void) override;
};

#endif  // JUMPER_H_
