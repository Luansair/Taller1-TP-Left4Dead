#ifndef THROWABLEFACTORY_H_
#define THROWABLEFACTORY_H_

#include "../../../../Common/include/Information/information_code.h"

class Throwable;

#include <memory>
#include "yaml-cpp/yaml.h"

class ThrowableFactory {
    uint32_t& code_counter;
public:
    explicit ThrowableFactory(uint32_t& code_counter);
    std::shared_ptr<Throwable> create(uint32_t *throwable_id, 
    uint8_t throwable_type, double x, double y, int8_t dir, 
    double dim_x, double dim_y, uint32_t thrower_id);
    void load_values(const YAML::Node &node, double *speed, double *scope, double *duration, double *damage);
};

#endif  // THROWABLEFACTORY_H_
