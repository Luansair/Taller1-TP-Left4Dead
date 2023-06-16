#include "../../include/GameLogic/match.h"

Match::Match(int32_t x_dimension, int32_t y_dimension) :
    soldiers(),
    zombies(),
    x_dim(x_dimension),
    y_dim(y_dimension) {
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

void Match::idle(uint32_t soldier_id, uint8_t state) {
    if (soldiers.count(soldier_id)>0) {
        std::shared_ptr<Soldier> &soldier = soldiers.at(soldier_id);
        soldier->idle(state);
    }
}

void Match::simulateStep(void) {
    for (auto & soldier : soldiers) {
        soldier.second->simulate(TIME, std::ref(soldiers), std::ref(zombies), x_dim, y_dim);
    }
    for (auto & zombie : zombies) {
        zombie.second->simulate(TIME, std::ref(soldiers), std::ref(zombies), x_dim, y_dim);
    }
}

std::vector<std::pair<uint16_t, ElementStateDTO >> Match::getElementStates() {
    std::vector<std::pair<uint16_t, ElementStateDTO>> elementStates;
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
