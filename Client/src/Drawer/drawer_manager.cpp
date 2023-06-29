//
// Created by luan on 07/06/23.
//
#include "../../include/Drawer/drawer_manager.h"

DrawerManager::DrawerManager(SDL2pp::Renderer &renderer) :
    animation_manager(renderer),
    renderer(renderer),
    actor_drawers() {
}


void DrawerManager::draw(std::uint32_t frame_ticks) {
    for (auto & pair_id_actor : actor_drawers) {
        ActorDrawer& actor_drawer = pair_id_actor.second;
        // if (pair_id_actor.first == 1) {
        //     std::cout << "id: " << pair_id_actor.first << "\n";
        //     std::cout << "x: " << pair_id_actor.second.position_x << "\n";
        //     std::cout << "y: " << pair_id_actor.second.position_y << "\n";
        //     std::cout << "type: " << unsigned(pair_id_actor.second.type) << "\n";
        //     std::cout << "vida: " << pair_id_actor.second.health << "\n";
        //     std::cout << "vida actual: " << pair_id_actor.second.actual_health << "\n";
        //     std::cout << "ammo: " << pair_id_actor.second.ammo << "\n";
        //     std::cout << "ammo actual: " << pair_id_actor.second.actual_ammo << "\n";
        //     std::cout << "tiempo: " << unsigned(pair_id_actor.second.timeleft) << "\n";
        //     std::cout << "-----------------------------------------" << "\n";
        // }
        actor_drawer.draw(frame_ticks);
        if (pair_id_actor.first < 100) {
            actor_drawer.drawBar();
        }
    }
}

void
DrawerManager::updateInfo(std::uint16_t actor_id, const ElementStateDTO &actor_state, std::int32_t window_x_pos,
                          std::int32_t window_width, std::int32_t window_height) {
    auto pair_id_actor_ptr = actor_drawers.find(actor_id);
    if (pair_id_actor_ptr == actor_drawers.end()) {
        pair_id_actor_ptr = addActor(actor_id, actor_state, window_x_pos, window_width, window_height);
    } else {
        ActorDrawer& found_actor = pair_id_actor_ptr->second;
        found_actor.updateInfo(actor_state, window_x_pos, window_width, window_height);

    }
    if (actor_state.is_dead == 1) {
        actor_drawers.erase(pair_id_actor_ptr);
    }
}


//-----------------------PRIVATE METHODS-------------------------------//
std::_Rb_tree_iterator<std::pair<const uint16_t, ActorDrawer>>
DrawerManager::addActor(std::uint16_t actor_id, const ElementStateDTO &actor_state, std::int32_t window_x_pos,
                        std::int32_t window_width, std::int32_t window_height) {
    auto res = actor_drawers.emplace(
            actor_id, ActorDrawer(animation_manager, renderer));
    if (!res.second) {
        throw std::runtime_error("DrawerManager::updateInfo. Attempt to "
                                 "insert new actor failed!.\n");
    }
    ActorDrawer& added_actor = res.first->second;
    added_actor.updateInfo(actor_state, window_x_pos, window_width, window_height);
    return res.first;
}

