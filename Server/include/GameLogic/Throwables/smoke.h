#ifndef SMOKE_H_
#define SMOKE_H_

#include "throwable.h"

class Smoke : public Throwable {

public:
    double damage;
    bool exploded = false;

    explicit Smoke(uint32_t throwable_id,
    double x, double y, double speed, double scope, double duration, 
    int8_t dir, double dim_x, double dim_y, uint32_t thrower_id, double damage);

    virtual void simulateThrow(std::chrono::_V2::system_clock::time_point real_time,
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies,  double dim_x, double dim_y) override;

    void simulateExplosion(std::map<uint32_t, std::shared_ptr<Zombie>>& zombies);

    virtual uint8_t getThrowerType() override;
    virtual uint8_t getAction() override;

};

#endif  // SMOKE_H_
