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

class GameVisual {
    SDL2pp::SDL sdl;
    SDL2pp::Window window;
    SDL2pp::Renderer renderer;
    std::map<std::uint16_t, Drawer> drawers;  // (id, drawer)

public:
    void init();

    void draw(unsigned int frameticks);
    void updateInfo(const GameStateFeedback& feed);
};

#endif //TP_VISUAL_GAME_H
