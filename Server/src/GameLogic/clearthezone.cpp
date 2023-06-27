#include "../../include/GameLogic/clearthezone.h"

ClearTheZone::ClearTheZone(double x_dimension, double y_dimension, uint8_t difficulty, uint32_t code) :
    Match(x_dimension, y_dimension, code) {
        configurate(difficulty);
}

void ClearTheZone::simulateStep(std::chrono::_V2::system_clock::time_point real_time) {
    double mass_center = calculate_mass_center();
    for (auto & zombie : zombies) {
        zombie.second->simulate(real_time, std::ref(soldiers), std::ref(zombies), std::ref(throwables), x_dim, y_dim, t_factory);
    }
    delete_dead_zombies();

    for (auto & throwable : throwables) {
        throwable.second->simulateThrow(real_time, std::ref(soldiers), std::ref(zombies), x_dim, y_dim);
    }
    // delete_inactive_throwables();
    for (auto & soldier : soldiers) {
        soldier.second->simulate(real_time, std::ref(soldiers), std::ref(zombies), std::ref(throwables), x_dim, y_dim, t_factory, mass_center);
    }
    delete_dead_soldiers();

    if ((dead_zombies_counter == zombie_counter) && finalizable) winMatch();
    if ((dead_soldiers_counter == soldier_counter) && finalizable) loseMatch();
}

void ClearTheZone::winMatch(void) {
    over = true;
}

void ClearTheZone::loseMatch(void) {
    over = true;
}

void ClearTheZone::configurate(uint8_t difficulty) {
    MatchConfigurator configurator;
    configurator.configurate(CLEAR_THE_ZONE, difficulty, zombies, soldiers, calculate_mass_center(), y_dim, &code_counter, &zombie_counter);
}