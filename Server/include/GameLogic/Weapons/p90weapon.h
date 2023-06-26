#ifndef P90WEAPON_H_
#define P90WEAPON_H_

/* Con rafagas de 10 balas, es un rifle más balanceado con una performance más consistente en largas
distancias.
Debe recargar el arma cada 30 rafagas. */

#include "weapon.h"

class P90Weapon : public Weapon {
private:
    uint32_t soldier_id;
    uint16_t ammo, actual_ammo;
    double damage, scope, damage_reduction_coef, bullet_speed;

public:
    explicit P90Weapon(uint32_t soldier_id, uint16_t ammo, double damage, double scope, double reduction, double bullet_speed);

    bool shoot(
    Position& from,
    int8_t dir,
    double dim_x,
    double time,
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies) override;

    void reload(void) override;

    uint16_t getAmmo(void) override;
    uint16_t getActualAmmo(void) override;
};

#endif  // P90WEAPON_H_
