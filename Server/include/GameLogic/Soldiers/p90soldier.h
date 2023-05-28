#ifndef P90SOLDIER_H_
#define P90SOLDIER_H_

#include "soldier.h"

class P90Soldier : public Soldier {
private:
    int32_t x;
    int32_t y;
    uint8_t health;
    unique_ptr<Weapon> weapon;
    unique_ptr<Grenade> grenade;

public:
    explicit P90Soldier(int32_t x, int32_t y, uint8_t health, unique_ptr<Weapon> &&weapon, unique_ptr<Grenade> &&grenade);
    
    void move(uint8_t state,
    uint8_t moveAxis,
    int8_t moveDirection,
    uint8_t moveForce) override;

    void shoot(void) override;

    void reload(void) override;

    void throwGrenade(void) override;

    void cGrenade(void) override;
};

#endif  // P90SOLDIER_H_
