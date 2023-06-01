#ifndef SOCKET_H_
#define SOCKET_H_

#include <cstdint>

class Socket {

public:
    virtual void sendData(const void *data, std::size_t amount) = 0;
    virtual void recvData(void *data, std::size_t amount) = 0;
    virtual ~Socket() = default;
};

#endif  // SOCKET_H_
