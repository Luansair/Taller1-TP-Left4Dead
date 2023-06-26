#ifndef SCOUTWEAPON_H_
#define SCOUTWEAPON_H_

#include "weapon.h"

/* A diferencia del IDF y P90, el Scout es un rifle que dispara de a 1 bala. No obstante cada bala daña a todo
infectado que se encuentre en su trayectoria (aunque el daño de cada impacto se verá reducido conforme la
bala pasa por más infectados).
Se recarga cada 20 balas. */

class ScoutWeapon : public Weapon {
private:
    uint32_t soldier_id;
    uint16_t ammo, actual_ammo;
    double damage, scope, damage_reduction_coef, bullet_speed;

public:
    explicit ScoutWeapon(uint32_t soldier_id, uint16_t ammo, double damage, double scope, double reduction, double bullet_speed);

    bool shoot(
    Position& from,
    int8_t dir,
    double dim_x,
    double time,
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies) override;

    uint16_t getAmmo(void) override;
    uint16_t getActualAmmo(void) override;

    void reload(void) override;

};

#endif  // SCOUTWEAPON_H_
