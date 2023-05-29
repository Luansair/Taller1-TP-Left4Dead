#include "../../include/GameLogic/match.h"

Match::Match(uint32_t x_dimension, uint32_t y_dimension) :
    soldiers{},
    zombies(),
    gamemap(x_dimension, y_dimension) {}

void Match::shoot(uint32_t soldier_id, uint8_t state) {
    if (soldiers.count(soldier_id)>0) {
        unique_ptr<Soldier> &soldier = soldiers.at(soldier_id);
        soldier->shoot(std::ref(gamemap), state);
    }
}

void Match::reload(uint32_t soldier_id, uint8_t state) {
    if (soldiers.count(soldier_id)>0) {
        unique_ptr<Soldier> &soldier = soldiers.at(soldier_id);
        soldier->reload(state);
    }
}

void Match::move(uint32_t soldier_id, 
    uint8_t state,
    uint8_t moveAxis,
    int8_t moveDirection,
    uint8_t moveForce) {

        if (soldiers.count(soldier_id)>0) {
            unique_ptr<Soldier> &soldier = soldiers.at(soldier_id);
            soldier->move(std::ref(gamemap), state, moveAxis, moveDirection, moveForce);
        }
    }

void Match::cGrenade(uint32_t soldier_id) {
    if (soldiers.count(soldier_id)>0) {
        unique_ptr<Soldier> &soldier = soldiers.at(soldier_id);
        soldier->cGrenade();
    }
}

void Match::throwGrenade(uint32_t soldier_id) {
    if (soldiers.count(soldier_id)>0) {
        unique_ptr<Soldier> &soldier = soldiers.at(soldier_id);
        soldier->throwGrenade(std::ref(gamemap));
    }
}

void Match::idle(uint32_t soldier_id) {
    // if (soldiers.count(soldier_id)>0) {
    //     Soldier &soldier = soldiers.at(soldier_id);
    //     soldier.idle();
    // }
}
