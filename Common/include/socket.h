#ifndef SOCKET_H_
#define SOCKET_H_

#include <cstdint>

class Socket {
    int fd;
    bool closed;

    explicit Socket(int sktfd);

    std::size_t sendSome(std::int8_t* data, std::size_t amount);
    std::size_t recvSome(std::int8_t* data, std::size_t amount);

public:
    Socket(const char *hostname, const char *servname);

    explicit Socket(const char *servname);

    Socket(const Socket&) = delete;
    Socket& operator=(const Socket&) = delete;

    Socket(Socket&&) noexcept;
    Socket& operator=(Socket&&);

    void send(std::int8_t* data, std::size_t amount);
    void recv(std::int8_t* data, std::size_t amount);

    Socket accept() const;

    void shutdown(int how) const;

    int close();

    ~Socket();
};

#endif  // SOCKET_H_
