#ifndef IDFWEAPON_H_
#define IDFWEAPON_H_

#include "weapon.h"

class IdfWeapon : public Weapon {
private:
    uint8_t ammo;
    uint8_t damage;
    uint8_t scope;
    uint8_t recoil;

public:
    explicit IdfWeapon(uint8_t ammo, uint8_t damage, uint8_t scope, uint8_t recoil);

    void shoot(void) override;

    void reload(void) override;

};

#endif  // IDFWEAPON_H_
