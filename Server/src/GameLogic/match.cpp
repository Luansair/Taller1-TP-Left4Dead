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
    soldier->setRandomPosition(std::ref(soldiers), std::ref(zombies), calculate_mass_center(), x_dim, y_dim);
    soldiers.emplace(soldier_id, std::move(soldier));
    soldier_counter += 1;
    finalizable = true;
}

void Match::setZombie(uint32_t zombie_id, uint8_t zombie_type) {
    ZombieFactory factory;
    std::shared_ptr<Zombie> zombie = factory.create(zombie_id, zombie_type);
    zombie->setRandomPosition(std::ref(soldiers), std::ref(zombies), x_dim, y_dim, calculate_mass_center());
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

void Match::reload(uint32_t soldier_id, uint8_t state) {
    if (soldiers.count(soldier_id)>0) {
        std::shared_ptr<Soldier> &soldier = soldiers.at(soldier_id);
        soldier->reload(state);
    }
}

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

void Match::killActor(uint32_t soldier_id, uint8_t state) {
        if (soldiers.count(soldier_id)>0) {
        std::shared_ptr<Soldier> &soldier = soldiers.at(soldier_id);
        soldier->alive = false;
    }
}

void Match::delete_dead_soldiers(void) {
    for (auto soldier = soldiers.begin(); soldier != soldiers.end(); soldier++) {
        if (soldier->second->isDead()) {
            //soldier = soldiers.erase(soldier);
            if (!soldier->second->counted) {
                dead_soldiers_counter += 1;
                soldier->second->counted = true;
                updateScore(soldier->first, std::ref(soldier->second));
            }
        }
    }
}

void Match::updateScore(uint32_t id, std::shared_ptr<Soldier>& soldier) {
    using YAML::LoadFile;
    using YAML::Node;
    std::unique_lock<std::mutex> lck(mtx);
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
    player[id_string]["bullets_fired"] = soldier->getBulletsFired();
    score[code]["players"].push_back(player);
    std::ofstream fout(SERVER_CONFIG_PATH "/score.yaml"); 
    fout << score; 
}

void Match::delete_dead_zombies(void) {
    for (auto zombie = zombies.begin(); zombie != zombies.end(); zombie++) {
        if (zombie->second->isDead()) {
            //zombies = zombiess.erase(zombies);
            if (!zombie->second->counted) {
                dead_zombies_counter += 1;
                zombie->second->counted = true;
            }
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
    // valores para rellenar
    uint16_t null_16 = 0;
    uint8_t null_8 = 0;

    for (const auto & throwable : throwables) {
        int id = throwable.second->getId();
        uint8_t actor_type = throwable.second->getThrowerType();
        uint8_t actor_action = throwable.second->getAction();
        int8_t actor_direction = throwable.second->getDirX();
        int position_x = throwable.second->getPosition().getXPos();
        int position_y = throwable.second->getPosition().getYPos();
        uint8_t is_active = throwable.second->isInactivefeedback();
        ElementStateDTO dto {actor_type, actor_action, 
        actor_direction, position_x, position_y, 
        null_16, null_16, null_16, null_16, null_8, is_active};
        elementStates.emplace_back(id, std::move(dto));
    }
    for (const auto & soldier : soldiers) {
        int id = soldier.second->getId();
        uint8_t actor_type = soldier.second->getSoldierType();
        uint8_t actor_action = soldier.second->getAction();
        int8_t actor_direction = soldier.second->getDirX();
        int position_x = soldier.second->getPosition().getXPos();
        int position_y = soldier.second->getPosition().getYPos();
        uint16_t health = soldier.second->getHealth();
        uint16_t actual_health = soldier.second->getActualHealth();
        uint16_t ammo = soldier.second->getAmmo();
        uint16_t actual_ammo = soldier.second->getActualAmmo();
        uint8_t time_left = soldier.second->getTimeLeft();
        uint8_t is_dead = soldier.second->isDeadFeedback();
        
        ElementStateDTO dto {actor_type, actor_action,
        actor_direction, position_x, position_y,
        health, actual_health, ammo, actual_ammo, time_left, is_dead};
        elementStates.emplace_back(id, std::move(dto));
    }
    for (const auto & zombie : zombies) {
        int id = zombie.second->getId();
        uint8_t actor_type = zombie.second->getZombieType();
        uint8_t actor_action = zombie.second->getAction();
        int8_t actor_direction = zombie.second->getDirX();
        int position_x = zombie.second->getPosition().getXPos();
        int position_y = zombie.second->getPosition().getYPos();
        uint16_t health = zombie.second->getHealth();
        uint16_t actual_health = zombie.second->getActualHealth();;
        uint8_t is_dead = zombie.second->isDeadFeedback();
        
        ElementStateDTO dto {actor_type, actor_action,
        actor_direction, position_x, position_y,
        health, actual_health, null_16, null_16, null_8, is_dead};
        elementStates.emplace_back(id, std::move(dto));
    }
    return elementStates;
}

GameStateFeedback Match::getMatchState(void) {
    return GameStateFeedback(std::move(getElementStates()));
}

std::vector<std::pair<uint16_t, ScoreDTO >> Match::getScores() {
    std::vector<std::pair<uint16_t, ScoreDTO>> scores;
    for (const auto & soldier : soldiers) {
        int id = soldier.second->getId();
        std::uint16_t seconds_alive = soldier.second->secondsAlive();
        std::uint16_t kills = soldier.second->getKills();
        int bullets_fired = soldier.second->getBulletsFired();
        
        ScoreDTO dto {seconds_alive, kills, bullets_fired};
        scores.emplace_back(id, std::move(dto));
    }
    return scores;
}

GameScoreFeedback Match::getMatchScores(void) {
    return GameScoreFeedback(std::move(getScores()));
}

bool Match::is_over(void) {
    return over;
}

std::map<uint32_t, std::shared_ptr<Soldier>>& Match::getSoldiers(void) {
    return std::ref(soldiers);
}

double Match::calculate_mass_center(void) {
    double sum = 0;
    double count = 0;
    for (const auto & soldier : soldiers) {
        if (soldier.second->isDead()) continue;
        sum += soldier.second->getPosition().getXPos();
        count += 1;
    }
    double center;
    if (count != 0) {
        center = sum / count;
    } else {
        center = x_dim * 0.5;
    }
    return center;
}
