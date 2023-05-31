// Copyright [2023] pgallino

#include <memory>
#include "../include/receiver.h"
#include "../../Common/include/Action/action_code.h"
#include "../../Common/include/Action/action_joingame.h"

#define SHUT_RDWR 2

Receiver::Receiver(Socket &&peer, GameManager& game_manager) :
    peer(std::move(peer)),
    protocol(this->peer),
    send_state_queue(5000),
    game_queue(nullptr),
    sender(this->peer, send_state_queue),
    game_manager(game_manager),
    is_running(true),
    keep_talking(true),
    joined(false),
    player_id(0),
    recv_action(nullptr) { }

void Receiver::run() {
    using std::cerr;
    using std::endl;
    using std::uint32_t;
    try {
    // modularizar. Meter en un metodo: joinear partida
    while (keep_talking && !joined) {
        // Excepcion si join falla (o nullptr). Excepcion: JoinFailed
        // Crear los comandos en una clase fuera del protocolo
        // Protocolo crea DTOs para evitar includes de todo el juego
        // Receiver puede pushear el command
        // Execute recibe siempre el Juego
        // Skippear lobby
        recv_action = protocol.recvAction();
        if(recv_action == nullptr)
            continue;

        if (recv_action->id == ActionID::JOIN) {
            // Dynamic_cast has more checks than static_cast but is slower.
            // It is safer in these cases to avoid undefined behaviour.
            auto* join_action = dynamic_cast<JoinGameAction *>(recv_action);
            joined = game_manager.joinGame(game_queue, send_state_queue,
                                           &player_id, join_action->game_code);

        } else if (recv_action->id == ActionID::CREATE) {
            game_manager.createGame(game_queue,
                                    send_state_queue,
                                    &player_id);
            joined = true;
        }
        delete recv_action;
    }
    if (joined) {
        sender.start();
    }
    // otro metodo privado: recibir acciones
    while (keep_talking) {
        recv_action = protocol.recvAction();
        if (recv_action == nullptr) {
            continue;
        }
        // Hacer el comando y pushearlo
        delete recv_action;
        recv_action = nullptr;
    }

    } catch (const ClosedSocket& err) {
        cerr << "In Receiver thread: " << err.what() << endl;
        // revisar catcheos
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
    // Just in case. Deleting nullptr has no effect.
    // Usar smart pointer
    delete recv_action;
}
