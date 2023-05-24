#ifndef SOCKET_H_
#define SOCKET_H_

#include <cstdint>
#include <stdexcept>

struct ClosedSocket : public std::exception {
    explicit ClosedSocket() = default;
    [[nodiscard]] virtual const char* what() const noexcept override {
        return "The socket is closed.\n";
    }
    virtual ~ClosedSocket() noexcept override = default;
};

class Socket {
    int fd;
    bool closed;

    explicit Socket(int sktfd);

    std::size_t sendSome(const void *data, std::size_t amount) const;
    std::size_t recvSome(void *data, std::size_t amount) const;

public:
    Socket(const char *hostname, const char *servname);

    explicit Socket(const char *servname);

    Socket(const Socket&) = delete;
    Socket& operator=(const Socket&) = delete;

    Socket(Socket&&) noexcept;
    Socket& operator=(Socket&&) noexcept;

    void sendData(const void *data, std::size_t amount);
    void recvData(void *data, std::size_t amount);

    [[nodiscard]] Socket acceptClient() const;

    int _shutdown(int how) const;

    int _close();

    ~Socket();
};

#endif  // SOCKET_H_
