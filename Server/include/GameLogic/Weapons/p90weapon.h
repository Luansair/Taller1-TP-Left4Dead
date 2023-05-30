#ifndef P90WEAPON_H_
#define P90WEAPON_H_

#define P90_DAMAGE 50
#define P90_AMMO 30

/* Con rafagas de 10 balas, es un rifle más balanceado con una performance más consistente en largas
distancias.
Debe recargar el arma cada 30 rafagas. */

#include "weapon.h"

class P90Weapon : public Weapon {
private:
    uint8_t ammo;
    uint8_t damage;

public:
    explicit P90Weapon(uint8_t ammo, uint8_t damage);

    void shoot(uint32_t x, uint32_t y, uint8_t dir, GameMap &map) override;

    void reload(uint8_t state) override;

};

#endif  // P90WEAPON_H_
