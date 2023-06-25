#ifndef IDFSOLDIER_H_
#define IDFSOLDIER_H_

#include "soldier.h"

class IdfSoldier : public Soldier {

public:
    explicit IdfSoldier(
    uint32_t soldier_id,
    double width,
    double height,
    double speed,
    double health,
    std::unique_ptr<Weapon>&& weapon);

    virtual uint8_t getSoldierType(void) override;

    virtual uint8_t getAction(void) override;

    virtual ~IdfSoldier() override = default;

};

#endif  // IDFSOLDIER_H_
