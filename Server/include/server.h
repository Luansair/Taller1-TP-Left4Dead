#ifndef SERVER_H_
#define SERVER_H_

#include "accepter.h"

class Server {
    Accepter accepter;

public:
    explicit Server(const char* servname);

    void init();

    ~Server();
};

#endif  // SERVER_H_
