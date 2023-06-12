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
    for (auto i = soldiers.begin(); i != soldiers.end(); i++) {
        i->second->simulate(TIME, std::ref(soldiers), std::ref(zombies), x_dim, y_dim);
    }
}

std::vector<std::pair<uint16_t, ElementStateDTO>> Match::getElementStates(void) {
    std::vector<std::pair<uint16_t, ElementStateDTO>> elementStates;
    for (auto i = soldiers.begin(); i != soldiers.end(); i++) {
        int id = i->second->getId();
        uint8_t actor_type = i->second->getSoldierType();
        uint8_t actor_action = i->second->getAction();
        int8_t actor_direction = i->second->getDirX();
        int position_x = i->second->getPosition().getXPos();
        int position_y = i->second->getPosition().getYPos();
        ElementStateDTO dto {actor_type, actor_action, actor_direction, position_x, position_y};
        elementStates.emplace_back(id, dto);
    }
    return elementStates;

}

GameStateFeedback Match::getMatchState(void) {
    return GameStateFeedback(std::move(getElementStates()));
}

std::map<uint32_t, std::shared_ptr<Soldier>>& Match::getSoldiers(void) {
    return std::ref(soldiers);
}
