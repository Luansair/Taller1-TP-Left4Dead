// Copyright [2023] pgallino

#include <memory>
#include "../include/receiver.h"
#include "../../Common/include/Action/action_code.h"

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
    using std::unique_ptr;
    while (keep_talking && !joined) {

        unique_ptr<PreGameCommand> pregame_cmd(
                protocol.recvPreGameCommand());
        if(pregame_cmd == nullptr)
            // Maybe protocol should throw this? It is to avoid infinite loop.
            throw std::runtime_error("Receiver::joinGame. Invalid pre game "
                                     "command.\n");

        joined = pregame_cmd->execute(game_manager, game_queue,
                                      send_state_queue, &player_id);

        /*
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
         */
    }
}

void Receiver::readCommands() {
    using std::unique_ptr;
    using std::shared_ptr;

    while (keep_talking) {
        unique_ptr<InGameCommand> ingame_cmd(
                protocol.recvInGameCommand(player_id));

        if (ingame_cmd == nullptr) {
            throw std::runtime_error("Receiver::readCommands. Invalid ingame "
                                     "command.\n");
        }
        game_queue->push(ingame_cmd.get());
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

        readCommands();

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
