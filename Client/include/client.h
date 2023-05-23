#ifndef CLIENT_H_
#define CLIENT_H_

#include "../../Common/include/socket.h"
#include "protocol.h"

class Client {
    Socket socket;
    Protocol protocol;

    void processEvent(std::uint32_t event_type, int key_code, bool* quit);
public:
    Client(const char* hostname, const char* servname);

    void init();

};

#endif  // CLIENT_H_
