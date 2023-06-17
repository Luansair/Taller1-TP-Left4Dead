#ifndef SCOUTSOLDIER_H_
#define SCOUTSOLDIER_H_

#include "soldier.h"

class ScoutSoldier : public Soldier {

public:
    explicit ScoutSoldier(
    uint32_t soldier_id,
    double width,
    double height,
    double speed,
    double health,
    std::unique_ptr<Weapon>&& weapon,
    std::unique_ptr<Grenade>&& grenade);

    virtual uint8_t getSoldierType(void) override;

    virtual uint8_t getAction(void) override;
};

#endif  // SCOUTSOLDIER_H_
