#ifndef DRAWER_PLAYER_H_
#define DRAWER_PLAYER_H_

#include <SDL2pp/SDL2pp.hh>
#include "drawer_animation.h"
#include "../../../Common/include/Feedback/state_player_dto.h"

// Decides which animation to display. AnimationDrawer handles the display.
class SoldierOneDrawer {
    AnimationDrawer run;
    AnimationDrawer idle;
    // More animations
    AnimationDrawer* actual_action;

public:
    explicit SoldierOneDrawer(SDL2pp::Renderer& renderer);

    void updateInfo(const PlayerStateDTO &player_state);
    void draw(unsigned int frame_ticks);
};

#endif  // DRAWER_PLAYER_H_
