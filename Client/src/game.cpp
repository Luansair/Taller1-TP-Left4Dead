//
// Created by luan on 17/06/23.
//
#include "../include/game.h"

ClientGame::ClientGame(
        Queue<std::shared_ptr<Information>>& actions_to_send,
        Queue<std::shared_ptr<Information>>& feedback_received) :
        config(),
        game_visual(config.window_width, config.window_height),
        feedback_received(feedback_received),
        quit(false),
        event_handler(actions_to_send, &quit) {
}

void ClientGame::launch() {

    std::shared_ptr<Information> information_ptr = nullptr;

    while (!quit)
    {
        unsigned int frame_ticks = SDL_GetTicks();

        event_handler.start();

        game_visual.clear();

        feedback_received.try_pop(information_ptr);

        if (information_ptr != nullptr) {
            game_visual.updateInfo(dynamic_cast<GameStateFeedback&>
                                   (*information_ptr));
        }

        game_visual.draw(frame_ticks);

        game_visual.present();

        SDL_Delay(1);
    }
}
