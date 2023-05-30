#ifndef IDFWEAPON_H_
#define IDFWEAPON_H_

#define IDF_DAMAGE 80
#define IDF_AMMO 50
#define DAMAGE_REDUCTION_COEF 0.8

#include "weapon.h"

/* Este rifle de asalto produce una rafaga de 20 balas con un daño considerable a corta distancia pero uno
mucho menor a larga distancia reflejando su imprecisión.
Debe recargar el arma cada 50 rafagas. */

class IdfWeapon : public Weapon {
private:
    uint8_t ammo;
    uint8_t damage;

public:
    explicit IdfWeapon(uint8_t ammo, uint8_t damage);

    void shoot(uint32_t x, uint32_t y, uint8_t dir, GameMap &map) override;

    void reload(uint8_t state) override;

};

#endif  // IDFWEAPON_H_
