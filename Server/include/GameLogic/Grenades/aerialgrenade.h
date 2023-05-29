#ifndef AERIALGRENADE_H_
#define AERIALGRENADE_H_

#include "grenade.h"

/* El bombardeo dejará caer granadas por todo el escenario salvo la zona cercana al jugador */

class AerialGrenade : public Grenade {
private:
    uint8_t damage;
    uint8_t cooldown;
    uint8_t scope;

public:
    explicit AerialGrenade(uint8_t damage, uint8_t cooldown, uint8_t scope);

    void throwg(GameMap &map) override;

};

#endif  // AERIALGRENADE_H_
