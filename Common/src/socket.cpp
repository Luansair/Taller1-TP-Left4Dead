#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <stdexcept>
#include <sstream>
#include <cstring>

#include "../include/socket.h"
#include "../include/resolver.h"

constexpr int MAX_PENDING_CONNECTIONS = 20;

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
            close(sktfd);
            continue;
        }
        fd = sktfd;
        closed = false;
    }
    if (closed || fd == -1) {
        throw std::runtime_error("Socket construction for client failed. "
                                 "Couldn't make connection.\n");
    }
}

Socket::Socket(const char* servname) {
    Resolver resolver = Resolver(nullptr, servname, true);
    closed = true;
    fd = -1;

    while (resolver.hasNext() && closed) {
        struct addrinfo* addr = resolver.nextAddr();

        int sktfd = socket(addr->ai_family, addr->ai_socktype,
                           addr->ai_protocol);
        if (sktfd == -1) {
            continue;
        }
        if (bind(sktfd, addr->ai_addr, addr->ai_addrlen) == -1) {
            close(sktfd);
            continue;
        }
        if (listen(sktfd, MAX_PENDING_CONNECTIONS) == -1) {
            close(sktfd);
            continue;
        }
        closed = false;
        fd = sktfd;
    }

    if (closed || fd == -1) {
        std::stringstream error_msg;
        error_msg << "Socket Construction for Server failed.\nServname: "
        << (servname ? servname : "null") << ".\nReason: " << strerror(errno)
        << std::endl;
        throw std::runtime_error(error_msg.str());
    }
}

Socket::Socket(Socket && other) noexcept {
    this->fd = other.fd;
    this->closed = other.closed;

    other.fd = -1;
    other.closed = true;
}

Socket& Socket::operator=(Socket&& other) noexcept {
    if (this == &other)
        return *this;

    if (!this->closed) {
        shutdown(fd, SHUT_RDWR);
        close(fd);
    }
    this->fd = other.fd;
    this->closed = other.closed;

    other.fd = -1;
    other.closed = true;

    return *this;
}

Socket::Socket(int sktfd) {
    fd = sktfd;
    closed = false;
}

std::size_t Socket::sendSome(const void *data, std::size_t amount)
const {
    ssize_t bytesSent = send(fd, data, amount, MSG_NOSIGNAL);
    if (bytesSent == -1) {
        if (errno == EPIPE || fd == -1) {
            throw ClosedSocket();
        } else {
            std::stringstream error_msg;
            error_msg << "Socket sendData failed for fd: " << fd << ".\nReason: "<<
                      strerror(errno) << std::endl;
            throw std::runtime_error(error_msg.str());
        }
    } else if (bytesSent == 0 && amount > 0) {
        std::stringstream error_msg;
        error_msg << "Socket sendData failed for fd: " << fd << ".\nReason: "<<
                  "sendData 0 bytes." << std::endl;
        throw std::runtime_error(error_msg.str());
    }
    return bytesSent;
}

std::size_t Socket::recvSome(void *data, std::size_t amount)
const {
    ssize_t bytesRecv = recv(fd, data, amount, 0);
    if (bytesRecv == 0 && amount > 0) {
        throw ClosedSocket();
    } else if (bytesRecv == -1) {
        std::stringstream error_msg;
        error_msg << "Socket recvData failed for fd: " << fd << ".\nReason: "<<
                  strerror(errno) << std::endl;
        throw std::runtime_error(error_msg.str());
    }
    return bytesRecv;
}

void Socket::sendData(const void *data, std::size_t amount) {
    size_t bytesSent = 0;
    while (bytesSent < amount) {
        bytesSent += sendSome((std::int8_t*)data + bytesSent,
                              amount - bytesSent);
    }
}

void Socket::recvData(void *data, std::size_t amount) {
    size_t bytesRecv = 0;
    while (bytesRecv < amount) {
        bytesRecv += recvSome((std::int8_t*)data + bytesRecv,
                              amount - bytesRecv);
    }
}

Socket Socket::acceptClient() const {
    int peerfd = accept(fd, nullptr, nullptr);
    if (peerfd == -1) {
        if (errno == EBADF || errno == EINVAL) {
            throw ClosedSocket();
        } else {
            std::stringstream error_msg;
            error_msg << "Socket acceptClient failed for fd: " << fd <<
            ".\nReason: "<< strerror(errno) << std::endl;
            throw std::runtime_error(error_msg.str());
        }
    }
    return Socket(peerfd);
}

int Socket::_shutdown(int how) const {
    return shutdown(fd, how);
}

int Socket::_close() {
    closed = true;
    return close(fd);
}

Socket::~Socket() {
    if (!closed) {
        shutdown(fd, SHUT_RDWR);
        close(fd);
    }
}
