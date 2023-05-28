#ifndef SMOKEGRENADE_H_
#define SMOKEGRENADE_H_

#include "grenade.h"

/* Las granadas de humo no producen daño pero los infectados quedan aturdidos
y dejan de correr y saltar por cierto tiempo aunque siguen caminando */

class SmokeGrenade : public Grenade {
private:
    uint8_t damage;
    uint8_t cooldown;
    uint8_t scope;

public:
    explicit SmokeGrenade(uint8_t damage, uint8_t cooldown, uint8_t scope);

    void throwg(void) override;

};

#endif  // SMOKEGRENADE_H_
