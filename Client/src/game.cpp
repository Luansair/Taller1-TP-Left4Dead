//
// Created by luan on 17/06/23.
//
#include "../include/game.h"

constexpr uint32_t MS_PER_FRAME = 16;

ClientGame::ClientGame(
        Queue<std::shared_ptr<Information>>& actions_to_send,
        Queue<std::shared_ptr<Information>>& feedback_received) :
        config(),
        game_visual(config.window_width, config.window_height),
        feedback_received(feedback_received),
        quit(false),
        event_handler(actions_to_send, &quit) {
}

void ClientGame::launch(ClientLobby &lobby) {
    using std::shared_ptr;
    using std::uint32_t;

    std::shared_ptr<Information> information_ptr = nullptr;

    while (!quit)
    {
        uint32_t start_milliseconds = SDL_GetTicks();

        event_handler.start();

        game_visual.clear();

        while(feedback_received.try_pop(information_ptr));

        if (information_ptr != nullptr) {
            game_visual.updateInfo(dynamic_cast<GameStateFeedback&>
                                   (*information_ptr));
        }
        game_visual.draw(start_milliseconds);

        game_visual.present();

        information_ptr = nullptr;

        uint32_t end_milliseconds = SDL_GetTicks();
        
        if (end_milliseconds - start_milliseconds < MS_PER_FRAME) {
            SDL_Delay(MS_PER_FRAME - end_milliseconds + start_milliseconds);
        }
    }
    lobby.showFinalStats(information_ptr);
}
