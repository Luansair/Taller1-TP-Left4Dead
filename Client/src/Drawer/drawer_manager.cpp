//
// Created by luan on 07/06/23.
//
#include "../../include/Drawer/drawer_manager.h"

DrawerManager::DrawerManager(SDL2pp::Renderer &renderer) :
    animation_manager(renderer),
    actor_drawers() {
}

void DrawerManager::draw(std::uint32_t frame_ticks, std::int32_t window_x_pos, std::int32_t window_width) {
    if (!game_over) {
        for (auto & pair_id_actor : actor_drawers) {
            ActorDrawer& actor_drawer = pair_id_actor.second;
            actor_drawer.draw(frame_ticks, window_x_pos, window_width);
        }
    }
    // DRAW FINAL WINDOW
}

void
DrawerManager::updateInfo(std::uint16_t actor_id, const ElementStateDTO &actor_state) {
    auto pair_id_actor_ptr = actor_drawers.find(actor_id);
    if (pair_id_actor_ptr == actor_drawers.end()) {
        addActor(actor_id, actor_state);
    } else {
        ActorDrawer& found_actor = pair_id_actor_ptr->second;
        found_actor.updateInfo(actor_state);
    }
}

void
DrawerManager::loadScore(std::uint16_t player_id, const ScoreDTO &score) {
    //aca cargar la info
    std::cout << "player_id: " << player_id << "\n";
    std::cout << "seconds_alive: " << score.seconds_alive << "\n";
    std::cout << "kills: " << score.kills << "\n";
    std::cout << "bullets_fired: " << score.bullets_fired << "\n";
    std::cout << "------------------------------------------------\n";
}

//-----------------------PRIVATE METHODS-------------------------------//
void
DrawerManager::addActor(std::uint16_t actor_id, const ElementStateDTO &actor_state) {
    auto res = actor_drawers.emplace(
            actor_id, ActorDrawer(animation_manager));
    if (!res.second) {
        throw std::runtime_error("DrawerManager::updateInfo. Attempt to "
                                 "insert new actor failed!.\n");
    }
    ActorDrawer& added_actor = res.first->second;
    added_actor.updateInfo(actor_state);
}

void DrawerManager::setGameOver(void) {
    game_over = true;
}
