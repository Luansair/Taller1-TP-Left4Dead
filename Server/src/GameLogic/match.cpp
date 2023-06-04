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
    std::shared_ptr<Soldier> soldier = factory.create(soldier_type);
    // los va poniendo apilados al lado del borde izq
    Position position(soldier->getWidth() + 1, soldier->getHeight() * soldier_counter + 1, soldier->getWidth(), soldier->getHeight());
    soldier->setPosition(std::move(position));
    soldiers.emplace(soldier_id, std::move(soldier));
    soldier_counter += 1;
}

void Match::shoot(uint32_t soldier_id, uint8_t state) {
    if (soldiers.count(soldier_id)>0) {
        // std::shared_ptr<Soldier> &soldier = soldiers.at(soldier_id);
        // soldier->shoot(state);
    }
}

void Match::reload(uint32_t soldier_id, uint8_t state) {
    if (soldiers.count(soldier_id)>0) {
        // std::shared_ptr<Soldier> &soldier = soldiers.at(soldier_id);
        // soldier->reload(state);
    }
}

void Match::move(uint32_t soldier_id, 
    uint8_t state,
    uint8_t moveAxis,
    int8_t moveDirection,
    uint8_t moveForce) {

        if (soldiers.count(soldier_id)>0) {
            // std::shared_ptr<Soldier> &soldier = soldiers.at(soldier_id);
            // soldier->move(state, moveAxis, moveDirection, moveForce);
        }
    }

void Match::cGrenade(uint32_t soldier_id) {
    if (soldiers.count(soldier_id)>0) {
        // std::shared_ptr<Soldier> &soldier = soldiers.at(soldier_id);
        // soldier->cGrenade();
    }
}

void Match::throwGrenade(uint32_t soldier_id) {
    if (soldiers.count(soldier_id)>0) {
        // std::shared_ptr<Soldier> &soldier = soldiers.at(soldier_id);
        // soldier->throwGrenade();
    }
}

void Match::idle(uint32_t soldier_id) {
    // if (soldiers.count(soldier_id)>0) {
    //     Soldier &soldier = soldiers.at(soldier_id);
    //     soldier.idle();
    // }
}
