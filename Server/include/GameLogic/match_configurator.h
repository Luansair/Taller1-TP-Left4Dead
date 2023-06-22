#ifndef MATCH_CONFIGURATOR_H_
#define MATCH_CONFIGURATOR_H_

#include <utility>
#include <cstdint>
#include <map>
#include <memory>
#include <string>

#include "../../../Common/include/Information/information_code.h"
#include "match.h"

class Zombie;
class Soldier;

class MatchConfigurator {
public:

    MatchConfigurator();

    void configurate(uint8_t mode, uint8_t difficulty,
    std::map<uint32_t, std::shared_ptr<Zombie>> &zombies,
    std::map<uint32_t, std::shared_ptr<Soldier>> &soldiers,
    double dim_x, double dim_y);

};

#endif  // MATCH_CONFIGURATOR_H_
