#ifndef POISON_H_
#define POISON_H_

#include "throwable.h"

class Poison : public Throwable {

public:
    double damage;

    explicit Poison(uint32_t throwable_id,
    double x, double y, double speed, double scope, double duration, 
    int8_t dir, double dim_x, double dim_y, double damage);

    virtual void simulateThrow(std::chrono::_V2::system_clock::time_point real_time, 
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies, double dim_x, double dim_y) override;

    virtual uint8_t getThrowerType() override;
    virtual uint8_t getAction() override;

};

#endif  // POISON_H_
