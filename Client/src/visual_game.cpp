//
// Created by luan on 09/06/23.
//

#include "../include/visual_game.h"

GameVisual::GameVisual(std::uint16_t window_width, std::uint16_t window_height) :
    sdl(SDL_INIT_VIDEO),
    window("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
           window_width, window_height, SDL_WINDOW_RESIZABLE),
    renderer(window, -1, SDL_RENDERER_ACCELERATED),
    drawer_manager(renderer) {
}

void GameVisual::draw(unsigned int frameticks) {
    drawer_manager.draw(frameticks);
}

void GameVisual::updateInfo(const GameStateFeedback &feed) {
    for (auto & pair_id_state : feed.elements) {
        std::uint16_t actor_id = pair_id_state.first;
        const ElementStateDTO& actor_state = pair_id_state.second;
        drawer_manager.updateInfo(actor_id, actor_state);
    }
}

void GameVisual::clear() {
    renderer.Clear();
}

void GameVisual::present() {
    renderer.Present();
}

