#ifndef IDFWEAPON_H_
#define IDFWEAPON_H_

#include "weapon.h"

/* Este rifle de asalto produce una rafaga de 20 balas con un daño considerable a corta distancia pero uno
mucho menor a larga distancia reflejando su imprecisión.
Debe recargar el arma cada 50 rafagas. */

class IdfWeapon : public Weapon {
private:
    uint32_t soldier_id;
    uint16_t ammo;
    uint16_t actual_ammo;
    double damage;
    double scope;
    double damage_reduction_coef;

public:
    explicit IdfWeapon(uint32_t soldier_id, uint16_t ammo, double damage, double scope, double reduction);

    bool shoot(
    Position& from,
    int8_t dir,
    double dim_x,
    double time,
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies) override;

    void reload(void) override;


};

#endif  // IDFWEAPON_H_
