#ifndef WITCH_H_
#define WITCH_H_

#include "zombie.h"

/* Esta infectada ocasionalmente se pone a gritar atrayendo a más infectados que llegaran corriendo a la
zona desde todas las direcciones. Los jugadores deberían eliminarla lo antes posible. */

class Witch : public Zombie {

public:
    explicit Witch(
    uint32_t zombie_id,
    double width,
    double height,
    double speed,
    double health);

    uint8_t getZombieType(void) override;
    uint8_t getAction(void) override;
};

#endif  // WITCH_H_
