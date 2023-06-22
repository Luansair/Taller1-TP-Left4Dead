//
// Created by luan on 09/06/23.
//

#include "../include/visual_game.h"

GameVisual::GameVisual(std::uint16_t window_width, std::uint16_t window_height) :
    sdl(SDL_INIT_VIDEO),
    window("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
           window_width, window_height, SDL_WINDOW_RESIZABLE),
    renderer(window, -1, SDL_RENDERER_ACCELERATED),
    drawer_manager(renderer),
    window_x_position(0) {
}

void GameVisual::draw(unsigned int frameticks) {
    drawer_manager.draw(frameticks, window_x_position, window.GetWidth());
}

void GameVisual::updateInfo(const GameStateFeedback &feed) {
    std::uint8_t player_count = 0;
    std::int32_t players_pos_x_sum = 0;

    for (auto & pair_id_state : feed.elements) {
        std::uint16_t actor_id = pair_id_state.first;
        const ElementStateDTO& actor_state = pair_id_state.second;
        drawer_manager.updateInfo(actor_id, actor_state);

        if (actor_id < 100) {
            player_count++;
            players_pos_x_sum += actor_state.position_x;
        }
    }
    if (player_count > 0) {
        window_x_position = (players_pos_x_sum / player_count) - window.GetWidth() / 2;
    }
}

void GameVisual::clear() {
    renderer.Clear();
}

void GameVisual::present() {
    renderer.Present();
}

