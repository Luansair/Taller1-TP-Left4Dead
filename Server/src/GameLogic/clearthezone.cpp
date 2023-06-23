#include "../../include/GameLogic/clearthezone.h"

ClearTheZone::ClearTheZone(double x_dimension, double y_dimension, uint8_t difficulty, uint32_t code) :
    Match(x_dimension, y_dimension, code) {
        configurate(difficulty);
}

void ClearTheZone::simulateStep(std::chrono::_V2::system_clock::time_point real_time) {
    for (auto & throwable : throwables) {
        throwable.second->simulateThrow(real_time, x_dim, y_dim);
    }
    delete_inactive_throwables();
    for (auto & zombie : zombies) {
        zombie.second->simulate(real_time, std::ref(soldiers), std::ref(zombies), std::ref(throwables), x_dim, y_dim);
    }
    delete_dead_zombies();
    for (auto & soldier : soldiers) {
        soldier.second->simulate(real_time, std::ref(soldiers), std::ref(zombies), x_dim, y_dim);
    }
    delete_dead_soldiers();

    if (zombies.size() == 0) winMatch();
    if (soldiers.size() == 0) loseMatch();
}

void ClearTheZone::winMatch(void) {}

void ClearTheZone::loseMatch(void) {}

void ClearTheZone::configurate(uint8_t difficulty) {
    MatchConfigurator configurator;
    configurator.configurate(CLEAR_THE_ZONE, difficulty, zombies, soldiers, x_dim, y_dim);
}