//
// Created by luan on 05/06/23.
//

#ifndef TP_VISUAL_GAME_H
#define TP_VISUAL_GAME_H

#include <SDL2pp/SDL2pp.hh>
#include <map>
#include "Drawer/drawer.h"
#include "../../Common/include/Information/information.h"
#include "../../Common/include/Information/feedback_server_gamestate.h"
#include "Drawer/drawer_manager.h"

class GameVisual {
    SDL2pp::SDL sdl;
    SDL2pp::Window window;
    SDL2pp::Renderer renderer;
    DrawerManager drawer_manager;  // (id, drawer)
    std::int32_t window_x_position;

public:
    GameVisual(std::uint16_t window_width, std::uint16_t window_height);

    void draw(unsigned int frameticks);
    void updateInfo(const GameStateFeedback& feed);

    void clear();
    void present();
};

#endif //TP_VISUAL_GAME_H
