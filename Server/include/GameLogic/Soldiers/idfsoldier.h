#ifndef IDFSOLDIER_H_
#define IDFSOLDIER_H_

#include "soldier.h"

class IdfSoldier : public Soldier {

public:
    explicit IdfSoldier(
    uint32_t soldier_id,
    int8_t dir,
    int8_t width,
    int8_t height,
    int8_t speed,
    int16_t health,
    std::unique_ptr<Weapon>&& weapon,
    std::unique_ptr<Grenade>&& grenade);

    virtual uint8_t getSoldierType(void) override;

    virtual uint8_t getAction(void) override;

};

#endif  // IDFSOLDIER_H_
