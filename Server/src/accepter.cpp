#include "../include/accepter.h"
#define SHUTDOWN_MODE 2

Accepter::Accepter(const std::string& servname) :
    skt(servname.c_str()),
    game() {
}

void Accepter::run(void) { try {
    while (true) {
        Socket peer = skt.accept();
        Handler* handler = new Handler(std::move(peer), std::ref(game));
        handlers.push_back(handler);
        handler->run();
        reap_dead();
    }
    } catch (const ClosedSocket& err) {
        kill_all();
    } catch (...) {
        std::cerr << "Something went wrong\n";
    }
}

void Accepter::close(void) {
    skt.shutdown(SHUTDOWN_MODE);
    skt.close();
}

void Accepter::kill_all(void) {
    for (auto & handler : handlers) {
        if (!handler->are_dead()) (handler)->kill();
        (handler)->join();
        delete handler;
    }
    handlers.clear();
}

void Accepter::reap_dead(void) {
    handlers.remove_if([](Handler* handler) { 
        if (handler->are_dead()) {
            handler->join();
            delete handler;
            return true;
        }
        return false;
    });
}
