#ifndef WITCH_H_
#define WITCH_H_

#include "zombie.h"

/* Esta infectada ocasionalmente se pone a gritar atrayendo a más infectados que llegaran corriendo a la
zona desde todas las direcciones. Los jugadores deberían eliminarla lo antes posible. */

class Witch: public Zombie {
private:
    int32_t x;
    int32_t y;
    uint8_t health;

public:
    explicit Witch(int32_t x, int32_t y, uint8_t health);
};

#endif  // WITCH_H_
