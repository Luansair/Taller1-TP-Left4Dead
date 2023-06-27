//
// Created by luan on 16/06/23.
//

#ifndef TP_GAME_H
#define TP_GAME_H

#include "visual_game.h"
#include "../../libs/queue.h"
#include "config_game.h"
#include "handler_event.h"
#include "lobby.h"
#include "music_game.h"

class ClientGame {
    GameConfig config;
    GameVisual game_visual;
    GameMusic game_music;
    Queue<std::shared_ptr<Information>>& feedback_received;

    bool quit;
    EventHandler event_handler;

public:
    ClientGame(
            Queue<std::shared_ptr<Information>>& actions_to_send,
            Queue<std::shared_ptr<Information>>& feedback_received);
    void launch(ClientLobby &lobby);
};

#endif //TP_GAME_H
