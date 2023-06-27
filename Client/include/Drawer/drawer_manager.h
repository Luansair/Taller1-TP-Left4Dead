//
// Created by luan on 07/06/23.
//

#ifndef TP_DRAWER_MANAGER_H
#define TP_DRAWER_MANAGER_H

#include <map>
#include "drawer_actor.h"

class DrawerManager {
    AnimationManager animation_manager;
    SDL2pp::Renderer& renderer;
    std::map<std::uint16_t, ActorDrawer> actor_drawers;

    std::_Rb_tree_iterator<std::pair<const uint16_t, ActorDrawer>>
    addActor(std::uint16_t actor_id, const ElementStateDTO &actor_state, std::int32_t window_x_pos,
             std::int32_t window_width, std::int32_t window_height);
public:
    explicit DrawerManager(SDL2pp::Renderer& renderer);

    void draw(std::uint32_t frame_ticks);

    void updateInfo(std::uint16_t actor_id, const ElementStateDTO &actor_state, std::int32_t window_x_pos,
                    std::int32_t window_width, std::int32_t window_height);
};

#endif //TP_DRAWER_MANAGER_H
