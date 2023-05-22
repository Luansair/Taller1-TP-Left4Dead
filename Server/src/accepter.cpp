#include "../include/accepter.h"
#define SHUT_RDWR 2

Accepter::Accepter(const std::string& servname) :
    skt(servname.c_str()),
    game_manager(),
    clients() {
}

void Accepter::run() { try {
    while (true) {
        Socket peer = skt.accept();
        auto* receiver = new Receiver(std::move(peer), game_manager);
        clients.push_back(receiver);
        // receiver->start()
        reapDead();
    }
    } catch (const ClosedSocket& err) {

    } catch (const std::exception& e) {
        std::cerr << "Something went wrong and an exception was caught: "
                  << e.what() << std::endl;
    }
}

void Accepter::stop() {
    skt.shutdown(SHUT_RDWR);
    skt.close();
}

void Accepter::killAll() {
    for (auto & client : clients) {
        if (!client->isDead()) (client)->stop();
        (client)->join();
        delete client;
    }
    clients.clear();
}

void Accepter::reapDead() {
    clients.remove_if([](Receiver* client) {
        if (client->isDead()) {
            client->join();
            delete client;
            return true;
        }
        return false;
    });
}

Accepter::~Accepter() {
    killAll();
}
