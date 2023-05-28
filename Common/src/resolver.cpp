#include <netdb.h>
#include <cstring>
#include <stdexcept>
#include <sstream>
#include "../include/resolver.h"

Resolver::Resolver(const char *hostname,
                   const char *servname,
                   bool is_passive) {
    struct addrinfo hints{};
    first = next = nullptr;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = is_passive ? AI_PASSIVE : 0;

    int ret = getaddrinfo(hostname, servname, &hints, &this->first);

    if (ret != 0) {
        if (ret == EAI_SYSTEM) {
            throw std::runtime_error("Resolver Error: Name resolution failed"
                                     ".\n");
        } else {
            std::stringstream error_msg;
            error_msg << "Resolver Error: " << gai_strerror(ret) << std::endl;
            throw std::runtime_error(error_msg.str());
        }
    }
    next = first;
}

Resolver::Resolver(Resolver&& other)  noexcept {
    first = other.first;
    next = other.next;
    other.first = nullptr;
    other.next = nullptr;
}

Resolver& Resolver::operator=(Resolver&& other) {
    if (this == &other)
        return *this;

    if (first)
        freeaddrinfo(first);

    first = other.first;
    next = other.next;
    other.first = nullptr;
    other.next = nullptr;

    return *this;
}

bool Resolver::hasNext() {
    return next != nullptr;
}

struct addrinfo* Resolver::nextAddr() {
    if (!hasNext()) {
        throw std::runtime_error("Error: Attempt to retrieve next address from Resolver when none exists. "
                                 "Remember to check if Resolver has more addresses with 'hasNext()' method. "
                                 "This is to avoid infinite loops.");
    }
    struct addrinfo* actual = next;
    next = actual->ai_next;
    return actual;
}

Resolver::~Resolver() {
    if (first) {
        freeaddrinfo(first);
    }
}