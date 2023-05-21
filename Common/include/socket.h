#ifndef SOCKET_H_
#define SOCKET_H_

#include <cstdint>

struct ClosedSocket : public std::exception {

};

class Socket {
    int fd;
    bool closed;

    explicit Socket(int sktfd);

    std::size_t sendSome(const std::int8_t* data, std::size_t amount) const;
    std::size_t recvSome(std::int8_t* data, std::size_t amount) const;

public:
    Socket(const char *hostname, const char *servname);

    explicit Socket(const char *servname);

    Socket(const Socket&) = delete;
    Socket& operator=(const Socket&) = delete;

    Socket(Socket&&) noexcept;
    Socket& operator=(Socket&&) noexcept;

    void send(const std::int8_t* data, std::size_t amount);
    void recv(std::int8_t* data, std::size_t amount);

    Socket accept() const;

    void shutdown(int how) const;

    int close();

    ~Socket();
};

#endif  // SOCKET_H_
