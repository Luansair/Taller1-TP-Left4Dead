//
// Created by luan on 09/06/23.
//

#include "../include/visual_game.h"
#include <iostream>

GameVisual::GameVisual(std::uint16_t window_width, std::uint16_t window_height) :
    sdl(SDL_INIT_VIDEO),
    window("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
           window_width, window_height, SDL_WINDOW_RESIZABLE),
    renderer(window, -1, SDL_RENDERER_ACCELERATED),
    drawer_manager(renderer),
    background_drawer(renderer, BACKGROUND_WAR1, window_width, window_height),
    window_x_position(0) {
}

void GameVisual::draw(unsigned int frameticks) {
    background_drawer.drawBehindLayers();
    drawer_manager.draw(frameticks);
}

void GameVisual::updateInfo(const GameStateFeedback &feed) {
    std::uint8_t player_count = 0;
    std::int32_t players_pos_x_sum = 0;

    for (auto & pair_id_state : feed.elements) {
        std::uint16_t actor_id = pair_id_state.first;
        const ElementStateDTO& actor_state = pair_id_state.second;
        drawer_manager.updateInfo(actor_id, actor_state, window_x_position, window.GetWidth(), window.GetHeight());

        if (actor_id < 100 && actor_state.is_dead != 1) {
            player_count++;
            players_pos_x_sum += actor_state.position_x;

        }
    }
    if (player_count > 0) {
        window_x_position = (players_pos_x_sum / player_count) - window.GetWidth() / 2;
    }
    background_drawer.updateInfo(window_x_position, window.GetWidth(), window.GetHeight());
}

void GameVisual::clear() {
    renderer.Clear();
}

void GameVisual::present() {
    renderer.Present();
}

