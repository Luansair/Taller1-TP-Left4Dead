//
// Created by luan on 07/06/23.
//

#ifndef TP_DRAWER_MANAGER_H
#define TP_DRAWER_MANAGER_H

#include <map>
#include "drawer_actor.h"
#include "../../../Common/include/Information/score_dto.h"

class DrawerManager {
    AnimationManager animation_manager;
    std::map<std::uint16_t, ActorDrawer> actor_drawers;
    bool game_over = false;

    void addActor(std::uint16_t actor_id, const ElementStateDTO &actor_state);
public:
    explicit DrawerManager(SDL2pp::Renderer& renderer);

    void draw(std::uint32_t frame_ticks, std::int32_t window_x_pos, std::int32_t window_width);

    void updateInfo(std::uint16_t actor_id, const ElementStateDTO &actor_state);
    void loadScore(std::uint16_t player_id, const ScoreDTO &score);

    void setGameOver(void);
};

#endif //TP_DRAWER_MANAGER_H
