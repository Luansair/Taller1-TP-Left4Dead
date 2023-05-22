#include "../include/server.h"

Server::Server(const std::string& servname) : accepter(servname) {}

void Server::init() {
    using std::string;
    using std::cin;

    accepter.start();
    string input;
    do {
        getline(cin, input);
    } while (input != "q");
}

Server::~Server() {
    accepter.stop();
    accepter.join();
}
