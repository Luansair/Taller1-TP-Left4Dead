#include <exception>
#include <SDL2pp/SDL2pp.hh>
#include "yaml-cpp/yaml.h"
#include "../include/client.h"
#include "../../Common/include/Information/Actions/game_join.h"
#include "../../Common/include/Information/Actions/game_create.h"
#include "../../Common/include/Information/feedback_server_joingame.h"


Client::Client(const char *hostname, const char *servname) :
    socket(hostname, servname) ,
    actions_to_send(5000),
    feedback_received(10000),
    sender(actions_to_send, socket),
    receiver(feedback_received, socket),
    client_game(actions_to_send, feedback_received) {
}

void Client::lobbyProcess() {
    using std::make_shared;
    using std::shared_ptr;

    using std::cout;
    using std::endl;

    bool joined = false;
    std::cout << "Waiting input. Use 'create' or 'join <code>' to join a "
                 "game."
              << std::endl;
    while (!joined)
    {
        std::string action;
        std::cin >> action;
        if (action == "join")
        {
            std::uint32_t game_code;
            std::cin >> game_code;

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
            actions_to_send.push(make_shared<CreateGameAction>());
            const std::shared_ptr<Information>& create_feed =
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
        }
    }
}


void Client::start() {

    sender.start();
    receiver.start();

    lobbyProcess();
    client_game.launch();
}

Client::~Client() {

    if (!receiver.isDead()) {
        receiver.stop();
    }
    if(!sender.isDead()) {
        sender.stop();
    }
    receiver.join();
    sender.join();
}
