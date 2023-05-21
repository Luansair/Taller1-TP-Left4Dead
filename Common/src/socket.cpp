#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <stdexcept>

#include "../include/socket.h"
#include "../include/resolver.h"

Socket::Socket(const char *hostname, const char *servname) {
    Resolver resolver(hostname, servname, false);

    closed = true;
    fd = -1;

    while (resolver.hasNext() && closed) {
        struct addrinfo* addr = resolver.nextAddr();

        int sktfd = socket(addr->ai_family,
                           addr->ai_socktype,
                           addr->ai_protocol);

        if (sktfd == -1) {
            continue;
        }
        if (connect(sktfd,
                    addr->ai_addr,
                    addr->ai_addrlen) == -1) {
            ::close(sktfd);
            continue;
        }
        fd = sktfd;
        closed = false;
    }
    if (closed) {
        throw std::runtime_error("Socket construction for client failed. "
                                 "Couldn't make connection.\n");
    }
}
