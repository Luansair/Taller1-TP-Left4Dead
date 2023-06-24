#include "../../include/GameLogic/match.h"
#include "yaml-cpp/yaml.h"

Match::Match(double x_dimension, double y_dimension, uint32_t code) :
    soldiers(),
    zombies(),
    x_dim(x_dimension),
    y_dim(y_dimension),
    code(code),
    configurator(),
    t_factory(std::ref(code_counter)) {
}

void Match::delete_soldier(uint32_t soldier_id) {
    if (soldiers.count(soldier_id)>0) {
        soldiers.erase(soldier_id);
    }
}

void Match::join(uint32_t soldier_id, uint8_t soldier_type) {
    SoldierFactory factory;
    std::shared_ptr<Soldier> soldier = factory.create(soldier_id, soldier_type);
    soldier->setRandomPosition(std::ref(soldiers), std::ref(zombies), x_dim, y_dim);
    soldiers.emplace(soldier_id, std::move(soldier));
    soldier_counter += 1;
}

void Match::setZombie(uint32_t zombie_id, uint8_t zombie_type) {
    ZombieFactory factory;
    std::shared_ptr<Zombie> zombie = factory.create(zombie_id, zombie_type);
    zombie->setRandomPosition(std::ref(soldiers), std::ref(zombies), x_dim, y_dim);
    zombies.emplace(zombie_id, std::move(zombie));
    zombie_counter += 1;
}

void Match::shoot(uint32_t soldier_id, uint8_t state) {
    if (soldiers.count(soldier_id)>0) {
        std::shared_ptr<Soldier> &soldier = soldiers.at(soldier_id);
        soldier->shoot(state);
    }
}

void Match::revive(uint32_t soldier_id, uint8_t state) {
    if (soldiers.count(soldier_id)>0) {
        std::shared_ptr<Soldier> &soldier = soldiers.at(soldier_id);
        soldier->revive(state);
    }
}

// void Match::reload(uint32_t soldier_id, uint8_t state) {
//     if (soldiers.count(soldier_id)>0) {
//         std::shared_ptr<Soldier> &soldier = soldiers.at(soldier_id);
//         soldier->reload(state);
//     }
// }

void Match::move(uint32_t soldier_id, 
    uint8_t state,
    uint8_t moveAxis,
    int8_t moveDirection,
    uint8_t moveForce) {

        if (soldiers.count(soldier_id)>0) {
            std::shared_ptr<Soldier> &soldier = soldiers.at(soldier_id);
            soldier->move(state, moveAxis, moveDirection, moveForce);
        }
    }

void Match::throwGrenade(uint32_t soldier_id, uint8_t state) {
    if (soldiers.count(soldier_id)>0) {
        std::shared_ptr<Soldier> &soldier = soldiers.at(soldier_id);
        soldier->throwGrenade(state);
    }
}

void Match::change_grenade(uint32_t soldier_id, uint8_t state) {
    if (soldiers.count(soldier_id)>0) {
        std::shared_ptr<Soldier> &soldier = soldiers.at(soldier_id);
        soldier->change_grenade_type(state);
    }
}

void Match::idle(uint32_t soldier_id, uint8_t state) {
    if (soldiers.count(soldier_id)>0) {
        std::shared_ptr<Soldier> &soldier = soldiers.at(soldier_id);
        soldier->idle(state);
    }
}

void Match::delete_dead_soldiers(void) {
    for (auto soldier = soldiers.begin(); soldier != soldiers.end(); ) {
        if (soldier->second->isDead()) {
            updateScore(soldier->first, std::ref(soldier->second));
            soldier = soldiers.erase(soldier);
        } else {
            ++soldier;
        }
    }
}

void Match::updateScore(uint32_t id, std::shared_ptr<Soldier>& soldier) {
    using YAML::LoadFile;
    using YAML::Node;
    Node score = LoadFile(SERVER_CONFIG_PATH "/score.yaml");
    const std::string id_string = std::to_string(id);
    const std::time_t rp = std::chrono::system_clock::to_time_t(create_time);
    std::string h(ctime(&rp)); //converting to c++ string
    if (!score[code]) {
        score[code]["time"] = h;
    }
    Node player;
    player[id_string] = YAML::Null; 
    player[id_string]["seconds_alive"] = soldier->secondsAlive();
    player[id_string]["kills"] = soldier->getKills();
    score[code]["players"].push_back(player);
    std::ofstream fout(SERVER_CONFIG_PATH "/score.yaml"); 
    fout << score; 
}

void Match::delete_dead_zombies(void) {
    for (auto zombie = zombies.begin(); zombie != zombies.end(); ) {
        if (zombie->second->isDead()) {
            zombie = zombies.erase(zombie);
        } else {
            ++zombie;
        }
    }   
}

void Match::delete_inactive_throwables(void) {
        for (auto throwable = throwables.begin(); throwable != throwables.end(); ) {
        if (throwable->second->isInactive()) {
            throwable = throwables.erase(throwable);
        } else {
            ++throwable;
        }
    }   
}

std::vector<std::pair<uint16_t, ElementStateDTO >> Match::getElementStates() {
    std::vector<std::pair<uint16_t, ElementStateDTO>> elementStates;

    for (const auto & throwable : throwables) {
        int id = throwable.second->getId();
        uint8_t actor_type = throwable.second->getThrowerType();
        uint8_t actor_action = throwable.second->getAction();
        int8_t actor_direction = throwable.second->getDirX();
        int position_x = throwable.second->getPosition().getXPos();
        int position_y = throwable.second->getPosition().getYPos();
        ElementStateDTO dto {actor_type, actor_action, actor_direction, position_x, position_y};
        elementStates.emplace_back(id, std::move(dto));
    }
    for (const auto & soldier : soldiers) {
        int id = soldier.second->getId();
        uint8_t actor_type = soldier.second->getSoldierType();
        uint8_t actor_action = soldier.second->getAction();
        int8_t actor_direction = soldier.second->getDirX();
        int position_x = soldier.second->getPosition().getXPos();
        int position_y = soldier.second->getPosition().getYPos();
        ElementStateDTO dto {actor_type, actor_action, actor_direction, position_x, position_y};
        elementStates.emplace_back(id, std::move(dto));
    }
    for (const auto & zombie : zombies) {
        int id = zombie.second->getId();
        uint8_t actor_type = zombie.second->getZombieType();
        uint8_t actor_action = zombie.second->getAction();
        int8_t actor_direction = zombie.second->getDirX();
        int position_x = zombie.second->getPosition().getXPos();
        int position_y = zombie.second->getPosition().getYPos();
        ElementStateDTO dto {actor_type, actor_action, actor_direction, position_x, position_y};
        elementStates.emplace_back(id, std::move(dto));
    }
    return elementStates;
}

GameStateFeedback Match::getMatchState(void) {
    return GameStateFeedback(std::move(getElementStates()));
}

std::map<uint32_t, std::shared_ptr<Soldier>>& Match::getSoldiers(void) {
    return std::ref(soldiers);
}
