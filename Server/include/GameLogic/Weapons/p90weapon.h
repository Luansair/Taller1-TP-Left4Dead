#ifndef P90WEAPON_H_
#define P90WEAPON_H_

/* Con rafagas de 10 balas, es un rifle más balanceado con una performance más consistente en largas
distancias.
Debe recargar el arma cada 30 rafagas. */

#include "weapon.h"

class P90Weapon : public Weapon {
private:
    uint8_t ammo;
    uint8_t actual_ammo;
    uint8_t damage;
    uint8_t scope;
    float damage_reduction_coef;

public:
    explicit P90Weapon(uint8_t ammo, uint8_t damage, uint8_t scope, float reduction);

    bool shoot(
    Position& from,
    int8_t dir,
    int32_t dim_x,
    uint16_t time,
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies) override;

    void reload(void) override;
};

#endif  // P90WEAPON_H_
