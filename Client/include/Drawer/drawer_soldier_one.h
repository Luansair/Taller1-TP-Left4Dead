#ifndef DRAWER_PLAYER_H_
#define DRAWER_PLAYER_H_

#include <SDL2pp/SDL2pp.hh>
#include "drawer_animation.h"
#include "../../../Common/include/Information/state_dto_element.h"
#include "drawer.h"

// Decides which animation to display. AnimationDrawer handles the display.
class SoldierOneDrawer : Drawer {
    AnimationDrawer run;
    AnimationDrawer idle;
    // More animations
    AnimationDrawer* actual_action;

public:
    explicit SoldierOneDrawer(SDL2pp::Renderer& renderer);

    void updateInfo(const ElementStateDTO &player_state);
    virtual void draw(unsigned int frame_ticks) override;
};

#endif  // DRAWER_PLAYER_H_
