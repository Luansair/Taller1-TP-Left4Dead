// Copyright [2023] pgallino

#include <memory>
#include "../include/receiver.h"
#include "../../Common/include/Action/action_code.h"
#include "../../Common/include/Action/action_joingame.h"

#define SHUT_RDWR 2

Receiver::Receiver(GameSocket &&peer, GameManager& game_manager) :
    peer(std::move(peer)),
    protocol(this->peer),
    send_state_queue(5000),
    game_queue(nullptr),
    sender(this->peer, send_state_queue),
    game_manager(game_manager),
    is_running(true),
    keep_talking(true),
    joined(false),
    player_id(0) {

}

// Excepcion si join falla (o nullptr). Excepcion: JoinFailed
// Crear los comandos en una clase fuera del protocolo
// Protocolo crea DTOs para evitar includes de todo el juego
// Receiver puede pushear el command
// Execute recibe siempre el Juego
// Skippear lobby

void Receiver::joinGame() {

    while (keep_talking && !joined) {

        std::unique_ptr<Action> recv_action(protocol.recvAction());
        if(recv_action == nullptr)
            continue;

        if (recv_action->id == ActionID::JOIN) {
            // Dynamic_cast has more checks than static_cast but is slower.
            // It is safer in these cases to avoid undefined behaviour.
            auto* join_action =
                    dynamic_cast<JoinGameAction *>(recv_action.get());
            joined = game_manager.joinGame(game_queue, send_state_queue,
                                           &player_id, join_action->game_code);

        } else if (recv_action->id == ActionID::CREATE) {
            game_manager.createGame(game_queue,
                                    send_state_queue,
                                    &player_id);
            joined = true;
        }
    }
}

void Receiver::readActions() {
    while (keep_talking) {
        std::unique_ptr<Action> recv_action(protocol.recvAction());
        if (recv_action == nullptr) {
            continue;
        }
        // Hacer el comando y pushearlo

    }
}

void Receiver::run() {
    using std::cerr;
    using std::endl;
    using std::uint32_t;
    try {

    joinGame();

    if (joined) {
        sender.start();
    }

    readActions();

    } catch (const ClosedSocket& err) {
        cerr << "In Receiver thread: " << err.what() << endl;
        is_running = false;
        keep_talking = false;
    } catch (const std::exception& e) {
        cerr << "An exception was caught in Receiver thread: "
        << e.what() << endl;
    } catch (...) {
        cerr << "An unknown exception was caught in Receiver thread." << endl;
    }
    is_running = false;
}

void Receiver::stop() {
    keep_talking = false;
    peer._shutdown(SHUT_RDWR);
    peer._close();
    send_state_queue.close();
}

bool Receiver::isDead() const {
    return !is_running;
}

Receiver::~Receiver() {
    if (joined) {
        if (!sender.isDead()) {
            sender.stop();
        }
        sender.join();
    }
}
