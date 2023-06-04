//
// Created by luan on 03/06/23.
//

#include "../../include/Drawer/drawer_soldier_one.h"
#include "../../../Common/include/Action/action_code.h"

SoldierOneDrawer::SoldierOneDrawer(SDL2pp::Renderer &renderer) :
    run(renderer, RESOURCES_PATH "/Soldier_1/Run.png"),
    idle(renderer, RESOURCES_PATH "/Soldier_1/Idle.png"),
    actual_action(&idle) {
}

void SoldierOneDrawer::updateInfo(const PlayerStateDTO &player_state) {
    AnimationDrawer* next_action = nullptr;

    if (player_state.action == ActionID::MOVE) {
        run.updateInfo({player_state.position_x,
                        player_state.position_y,
                        player_state.direction} );
        next_action = &run;

    } else if (player_state.action == ActionID::IDLE) {
        idle.updateInfo( {player_state.position_x,
                          player_state.position_y,
                          player_state.direction} );
        next_action = &idle;
    }

    if (next_action == nullptr) {
        throw std::runtime_error("SoldierOneDrawer::updateInfo. Invalid "
                                 "Action.\n");
    }

    if (next_action != actual_action) {
        actual_action->reset();
        actual_action = next_action;
    }
}

void SoldierOneDrawer::draw(unsigned int frame_ticks) {
    actual_action->draw(frame_ticks);
}


