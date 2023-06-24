#ifndef MATCH_CONFIGURATOR_H_
#define MATCH_CONFIGURATOR_H_

#include <utility>
#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include "Zombies/zombiefactory.h"

#include "../../../Common/include/Information/information_code.h"


class Zombie;
class Soldier;

class MatchConfigurator {
public:
    int amount_infected = 0;
    int amount_venom = 0;
    int amount_witch = 0;
    int amount_jumper = 0;
    int amount_spear = 0;
    int begin = SOLDIERS_MAX + 1;
    int total = 0;
    MatchConfigurator();

    void configurate(uint8_t mode, uint8_t difficulty,
    std::map<uint32_t, std::shared_ptr<Zombie>> &zombies,
    std::map<uint32_t, std::shared_ptr<Soldier>> &soldiers,
    double dim_x, double dim_y);

    void add_zombies(int amount, std::map<uint32_t, std::shared_ptr<Zombie>> &zombies,
    std::map<uint32_t, std::shared_ptr<Soldier>> &soldiers,
    double dim_x, double dim_y);

};

#endif  // MATCH_CONFIGURATOR_H_
