#ifndef CLIENT_H_
#define CLIENT_H_

#include "../../Common/include/socket.h"
#include "protocol.h"

class Client {
    Socket socket;
    Protocol protocol;

    void processEvent(const SDL_Event& event, bool* quit);
public:
    Client(const char* hostname, const char* servname);

    void init();

};

#endif  // CLIENT_H_
