#include "../../include/GameLogic/survival.h"

Survival::Survival(double x_dimension, double y_dimension, uint8_t difficulty, uint32_t code) :
    Match(x_dimension, y_dimension, code) {
        configurate(difficulty);
}

void Survival::simulateStep(std::chrono::_V2::steady_clock::time_point real_time) {
    for (auto & zombie : zombies) {
        zombie.second->simulate(real_time, std::ref(soldiers), std::ref(zombies), x_dim, y_dim);
    }
    delete_dead_zombies();
    for (auto & soldier : soldiers) {
        soldier.second->simulate(real_time, std::ref(soldiers), std::ref(zombies), x_dim, y_dim);
    }
    delete_dead_soldiers();

    if (soldiers.size() == 0) loseMatch();
}

void Survival::loseMatch(void) {}

void Survival::configurate(uint8_t difficulty) {
    MatchConfigurator configurator;
    configurator.configurate(SURVIVAL, difficulty, zombies, soldiers, x_dim, y_dim);
}