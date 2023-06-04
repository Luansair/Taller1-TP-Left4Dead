#ifndef SCOUTWEAPON_H_
#define SCOUTWEAPON_H_

#define DAMAGE_REDUCTION_COEF 0.8
#define SCOUT_DAMAGE 60
#define SCOUT_AMMO 20

#include "weapon.h"

/* A diferencia del IDF y P90, el Scout es un rifle que dispara de a 1 bala. No obstante cada bala daña a todo
infectado que se encuentre en su trayectoria (aunque el daño de cada impacto se verá reducido conforme la
bala pasa por más infectados).
Se recarga cada 20 balas. */

class ScoutWeapon : public Weapon {
private:
    uint8_t ammo;
    uint8_t damage;
    uint8_t scope;

public:
    explicit ScoutWeapon(uint8_t ammo, uint8_t damage, uint8_t scope);

    bool shoot(
    Position& from,
    int8_t dir,
    uint16_t time,
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies) override;

    void reload(void) override;

};

#endif  // SCOUTWEAPON_H_
