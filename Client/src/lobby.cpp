//
// Created by luan on 17/06/23.
//
#include <iostream>
#include "../include/lobby.h"
#include "../../Common/include/Information/feedback_server_joingame.h"
#include "../../Common/include/Information/feedback_server_creategame.h"
#include "../../Common/include/Information/Requests/pick_soldier_idf.h"
#include "../../Common/include/Information/Requests/pick_soldier_p90.h"
#include "../../Common/include/Information/Requests/pick_soldier_scout.h"
#include "../../Common/include/Information/Actions/game_join.h"
#include "../../Common/include/Information/Actions/game_create.h"
#include "LobbyUI/lobbywindow.h"
#include "LobbyUI/gameresultwindow.h"

ClientLobby::ClientLobby(Queue<std::shared_ptr<Information>> &actions_to_send,
                         Queue<std::shared_ptr<Information>> &feedback_received, int argc, char **argv) :
            argc(argc),
            argv(argv),
            actions_to_send(actions_to_send),
            feedback_received(feedback_received),
            soldier_picked(false),
            joined(false) {
}

void ClientLobby::launch(bool *joined) {
    QApplication visualization_app(argc, argv);

    LobbyWindow visual_lobby(actions_to_send, feedback_received, nullptr);

    visual_lobby.show();

    if (visualization_app.exec()) {
        throw std::runtime_error("ClientLobby::launch(). QT application bad end.\n");
    }


}

void ClientLobby::showFinalStats(const GameScoreFeedback &info) {
    QApplication visualization_app(argc, argv);

    GameResultWindow game_result(info);

    game_result.show();

    if (visualization_app.exec()) {
        throw std::runtime_error("ClientLobby::launch(). QT application bad end.\n");
    }
}
