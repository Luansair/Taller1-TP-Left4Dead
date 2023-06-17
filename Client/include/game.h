//
// Created by luan on 16/06/23.
//

#ifndef TP_GAME_H
#define TP_GAME_H

#include "visual_game.h"
#include "../../libs/queue.h"
#include "config_game.h"
#include "handler_event.h"

class ClientGame {
    GameConfig config;
    GameVisual game_visual;
    Queue<std::shared_ptr<Information>>& feedback_received;

    bool quit;
    EventHandler event_handler;

public:
    ClientGame(
            Queue<std::shared_ptr<Information>>& actions_to_send,
            Queue<std::shared_ptr<Information>>& feedback_received);
    void launch();
};

#endif //TP_GAME_H
