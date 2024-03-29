#ifndef INFECTED_H_
#define INFECTED_H_

#include "zombie.h"

/* Los infectados caminan o permanecen quietos en las calles si no son molestados pero la mayoría
empezará a caminar hacia los jugadores en cuanto estén a la vista para matarlos (sea a través de golpes,
zarpazos o mordidas). */

class Infected : public Zombie {

public:
    explicit Infected(
    uint32_t zombie_id,
    double width,
    double height,
    double speed,
    double health,
    double sight,
    double listening_range,
    double hit_scope,
    double damage,
    double die_cooldown,
    double stunned_cooldown);

    uint8_t getZombieType(void) override;
    uint8_t getAction(void) override;
};

#endif  // INFECTED_H_
