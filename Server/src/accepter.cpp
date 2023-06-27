#include "../include/accepter.h"

constexpr std::uint32_t MAX_GAMES = 10;

Accepter::Accepter(const std::string& servname) :
    skt(servname.c_str()),
    game_manager(),
    clients() {
}

void Accepter::run() {
    using std::exception;
    using std::cerr;
    using std::endl;

    try {
    while (true) {
        GameSocket peer = skt.acceptClient();
        auto* receiver = new Receiver(std::move(peer), game_manager);
        clients.push_back(receiver);
        receiver->start();
        reapDead();
    }
    } catch (const ClosedSocket& err) {
        cerr << "In Accepter Thread: " << err.what() << endl;
    } catch (const exception& e) {
        cerr << "An exception was caught in the Accepter thread: "
                  << e.what() << endl;
    } catch (...) {
        cerr << "An unknown exception was caught in the Accepter thread." <<
        endl;
    }
}

void Accepter::stop() {
    skt._shutdown(SHUT_RDWR);
    skt._close();
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
