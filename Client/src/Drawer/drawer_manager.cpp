//
// Created by luan on 07/06/23.
//
#include "../../include/Drawer/drawer_manager.h"

DrawerManager::DrawerManager(SDL2pp::Renderer &renderer) :
    animation_manager(renderer),
    actor_drawers() {
}

void DrawerManager::draw(unsigned int frame_ticks) {
    for (auto & pair_id_actor : actor_drawers) {
        ActorDrawer& actor_drawer = pair_id_actor.second;
        actor_drawer.draw(frame_ticks);
    }
}

void
DrawerManager::updateInfo(std::uint16_t actor_id, ElementStateDTO actor_state) {
    auto pair_id_actor_ptr = actor_drawers.find(actor_id);
    if (pair_id_actor_ptr == actor_drawers.end()) {
        addActor(actor_id, actor_state);
    } else {
        ActorDrawer& found_actor = pair_id_actor_ptr->second;
        found_actor.updateInfo(actor_state);
    }
}

//-----------------------PRIVATE METHODS-------------------------------//
void
DrawerManager::addActor(std::uint16_t actor_id, ElementStateDTO actor_state) {
    auto res = actor_drawers.emplace(
            actor_id, ActorDrawer(animation_manager));
    if (!res.second) {
        throw std::runtime_error("DrawerManager::updateInfo. Attempt to "
                                 "insert new actor failed!.\n");
    }
    ActorDrawer& added_actor = res.first->second;
    added_actor.updateInfo(actor_state);
}


