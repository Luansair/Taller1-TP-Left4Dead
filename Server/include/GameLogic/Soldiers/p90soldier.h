#ifndef P90SOLDIER_H_
#define P90SOLDIER_H_

#include "soldier.h"

class P90Soldier : public Soldier {

public:
    explicit P90Soldier(
    uint32_t soldier_id,
    double width,
    double height,
    double speed,
    double health,
    std::unique_ptr<Weapon>&& weapon,
    double revive_radius,
    uint8_t t_type,
    double revive_cooldown,
    double reload_cooldown,
    double throw_cooldown,
    double throw_duration);

    void simulateThrow(std::chrono::_V2::system_clock::time_point real_time, double dim_x, double dim_y,
    std::map<uint32_t, std::shared_ptr<Throwable>>& throwables, ThrowableFactory& factory) override;

    virtual uint8_t getSoldierType(void) override;
    
    virtual uint8_t getAction(void) override;

    virtual ~P90Soldier() override = default;
};

#endif  // P90SOLDIER_H_
