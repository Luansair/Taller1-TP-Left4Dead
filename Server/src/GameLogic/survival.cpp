#include "../../include/GameLogic/survival.h"

Survival::Survival(double x_dimension, double y_dimension, uint8_t difficulty, uint32_t code) :
    Match(x_dimension, y_dimension, code) {
        configurate(difficulty);
}

void Survival::simulateStep(std::chrono::_V2::system_clock::time_point real_time) {
    for (auto & zombie : zombies) {
        zombie.second->simulate(real_time, std::ref(soldiers), std::ref(zombies), std::ref(throwables), x_dim, y_dim, t_factory);
    }
    //delete_dead_zombies();

    for (auto & throwable : throwables) {
        throwable.second->simulateThrow(real_time, std::ref(soldiers), std::ref(zombies), x_dim, y_dim);
    }
    // delete_inactive_throwables();

    for (auto & soldier : soldiers) {
        soldier.second->simulate(real_time, std::ref(soldiers), std::ref(zombies), std::ref(throwables), x_dim, y_dim, t_factory);
    }
    delete_dead_soldiers();

    if ((dead_soldiers_counter == soldier_counter) && finalizable) loseMatch();
    std::chrono::duration<double> time = real_time - actual_time;
    if (time.count() > 30) {
        actual_time = real_time;
        add_zombies();
    }
}

void Survival::loseMatch(void) {
    over = true;
}

void Survival::configurate(uint8_t difficulty) {
    configurator.configurate(SURVIVAL, difficulty, zombies, soldiers, x_dim, y_dim, &code_counter, &zombie_counter);
}

void Survival::add_zombies(void) {
    configurator.add_zombies(1, zombies, soldiers, x_dim, y_dim, &code_counter, &zombie_counter);
}