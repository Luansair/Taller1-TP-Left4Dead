#ifndef SOCKET_GAME_H_
#define SOCKET_GAME_H_

#include <cstdint>
#include <stdexcept>
#include "socket.h"

struct ClosedSocket : public std::exception {
    explicit ClosedSocket() = default;
    [[nodiscard]] virtual const char* what() const noexcept override {
        return "The socket is closed.\n";
    }
    virtual ~ClosedSocket() noexcept override = default;
};

class GameSocket : public Socket {
    int fd;
    bool closed;

    explicit GameSocket(int sktfd);

    std::size_t sendSome(const void *data, std::size_t amount) const;
    std::size_t recvSome(void *data, std::size_t amount) const;

public:
    GameSocket(const char *hostname, const char *servname);

    explicit GameSocket(const char *servname);

    GameSocket(const GameSocket&) = delete;
    GameSocket& operator=(const GameSocket&) = delete;

    GameSocket(GameSocket&&) noexcept;
    GameSocket& operator=(GameSocket&&) noexcept;

    virtual void sendData(const void *data, std::size_t amount) override;
    virtual void recvData(void *data, std::size_t amount) override;

    [[nodiscard]] GameSocket acceptClient() const;

    int _shutdown(int how) const;

    int _close();

    ~GameSocket() override;
};

#endif  // SOCKET_GAME_H_
