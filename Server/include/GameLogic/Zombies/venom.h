#ifndef VENOM_H_
#define VENOM_H_

#include "zombie.h"

/* Con una apariencia totalmente humana, Venom lanza un líquido/gas corrosivo. Puede lanzarlo como un
spray desde corta distancia (como se muestra en la figura) así como también puede lanzar bolas de este
líquido desde largas distancias.
El spray daña a todo jugador que esté en contacto con él */

class Venom : public Zombie {

public:
    explicit Venom(
    uint32_t zombie_id,
    int8_t dir,
    int8_t width,
    int8_t height,
    int8_t speed,
    int16_t health);

    uint8_t getZombieType(void) override;
};

#endif  // VENOM_H_

