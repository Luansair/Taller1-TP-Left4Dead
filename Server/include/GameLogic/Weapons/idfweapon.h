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
    uint8_t scope;

public:
    explicit IdfWeapon(uint8_t ammo, uint8_t damage, uint8_t scope);

    bool shoot(
    Position& from,
    int8_t dir,
    uint16_t time,
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies) override;

    void reload(void) override;


};

#endif  // IDFWEAPON_H_
