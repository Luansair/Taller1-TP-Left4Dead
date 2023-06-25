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

ClientLobby::ClientLobby(Queue<std::shared_ptr<Information>> &actions_to_send,
                         Queue<std::shared_ptr<Information>> &feedback_received, int argc, char **argv) :
            argc(argc),
            argv(argv),
            actions_to_send(actions_to_send),
            feedback_received(feedback_received),
            soldier_picked(false),
            joined(false) {
}

void ClientLobby::pickSoldier() {
    using std::make_shared;
    using std::cout;
    using std::endl;
    using std::string;
    using std::cin;

    cout << "Pick a soldier: \n"
            "> idfsoldier\n"
            "> p90soldier\n"
            "> scoutsoldier" << endl;

    while (!soldier_picked) {

        string soldier_type_string;
        cin >> soldier_type_string;
        if (soldier_type_string == "idfsoldier") {
            actions_to_send.push(make_shared<PickIdfSoldierRequest>());
            soldier_picked = true;
        } else if (soldier_type_string == "p90soldier") {
            actions_to_send.push(make_shared<PickP90SoldierRequest>());
            soldier_picked = true;
        } else if (soldier_type_string == "scoutsoldier") {
            actions_to_send.push(make_shared<PickScoutSoldierRequest>());
            soldier_picked = true;
        } else {
            cout << "Invalid soldier type. "
                    "Pick a soldier: \n> idfsoldier\n> p90soldier\n> scoutsoldier" << endl;
        }
    }
}

std::uint8_t ClientLobby::pickGameMode() {
    using std::make_shared;
    using std::cout;
    using std::endl;
    using std::string;
    using std::cin;

    cout << "Select GameMode: \n"
            "> survival\n"
            "> clearzone"
            << endl;

    while (true) {

        string mode_type_string;
        cin >> mode_type_string;
        if (mode_type_string == "survival") {
            return REQUEST_SURVIVAL;
        } else if (mode_type_string == "clearzone") {
            return REQUEST_CLEAR_THE_ZONE;
        } else {
            cout << "Invalid mode type. "
                    "Select GameMode: \n> survival\n> clearzone" << endl;
        }
    }
}

std::uint8_t ClientLobby::pickGameDifficulty() {
    using std::make_shared;
    using std::cout;
    using std::endl;
    using std::string;
    using std::cin;

    cout << "Select Difficulty: \n"
            "> easy\n"
            "> normal\n"
            "> hard\n"
            "> insane"
            << endl;

    while (true) {

        string mode_type_string;
        cin >> mode_type_string;
        if (mode_type_string == "easy") {
            return REQUEST_EASY;
        } else if (mode_type_string == "normal") {
            return REQUEST_NORMAL;
        } else if (mode_type_string == "hard") {
            return REQUEST_HARD;
        } else if (mode_type_string == "insane") {
            return REQUEST_INSANE;
        } else {
                cout << "Select Difficulty: \n"
                        "> easy\n"
                        "> normal\n"
                        "> hard\n"
                        "> insane"
                        << endl;
        }
    }
}

void ClientLobby::joinGame() {
    using std::make_shared;
    using std::shared_ptr;
    using std::cout;
    using std::endl;
    using std::string;
    using std::cin;

    cout << "Waiting input. Use 'create' or 'join <code>' to join a "
                 "game."
              << endl;
              
     while (!joined)
    {
        string action;
        cin >> action;
        if (action == "join")
        {
            std::uint32_t game_code;
            cin >> game_code;

            actions_to_send.push(
                    make_shared<JoinGameAction>(game_code));
            const auto& feed = feedback_received.pop();

            if (feed == nullptr) {
                throw std::runtime_error("Client::lobbyProcess. "
                                         "Feedback for join is null.\n");
            }
            const auto& join_feed = dynamic_cast<JoinGameFeedback&>(*feed);
            if (join_feed.joined == 0) {
                cout << "Joined failed for code: " << game_code << endl;
            } else if (join_feed.joined == 1) {
                cout << "Joined game with code: " << game_code << endl;
                joined = true;
            }
        }
        else if (action == "create")
        {
            std::uint8_t gamemode = pickGameMode();
            std::uint8_t gamedifficulty = pickGameDifficulty();
            actions_to_send.push(make_shared<CreateGameAction>(gamemode, gamedifficulty));
            const shared_ptr<Information>& create_feed =
                    feedback_received.pop();

            if (create_feed == nullptr)
            {
                throw std::runtime_error("Client::lobbyProcess. "
                                         "CreateFeedback is null.\n");
            }
            std::cout <<
            dynamic_cast<CreateGameFeedback *>(create_feed.get())->game_code
                      << std::endl;
            joined = true;
        } else {
            cout << "Invalid request. Use 'create' or 'join <code>' to join a game" << endl;
        }
    }
}

void ClientLobby::launch() {
    QApplication visualization_app(argc, argv);
    LobbyWindow visual_lobby;
    visual_lobby.show();

    if (visualization_app.exec()) {
        throw std::runtime_error("ClientLobby::launch(). QT application bad end.\n");
    }

    joinGame();
    pickSoldier();
}
