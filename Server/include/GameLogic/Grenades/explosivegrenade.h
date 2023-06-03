#ifndef EXPLOSIVEGRENADE_H_
#define EXPLOSIVEGRENADE_H_

#include "grenade.h"

/* Las granadas convencionales producen una explosion que  daña a todos los infectados de la zona.
Cuidado que la explosion puede dañar a otros jugadores. */

class ExplosiveGrenade : public Grenade {
private:
    uint8_t damage;
    uint8_t cooldown;
    uint8_t scope;

public:
    explicit ExplosiveGrenade(uint8_t damage, uint8_t cooldown, uint8_t scope);

    void throwg(uint32_t x, uint32_t y, uint8_t dir) override;

};

#endif  // EXPLOSIVEGRENADE_H_
