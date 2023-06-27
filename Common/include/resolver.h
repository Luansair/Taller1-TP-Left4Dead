#ifndef RESOLVER_H_
#define RESOLVER_H_

#include <string>

class Resolver {
    struct addrinfo* first;
    struct addrinfo* next;

public:
    Resolver(
            const char* hostname,
            const char* servname,
            bool is_passive);

    Resolver(const Resolver&) = delete;
    Resolver& operator=(const Resolver&) = delete;

    Resolver(Resolver&&) noexcept;
    Resolver& operator=(Resolver&&);

    bool hasNext();

    struct addrinfo* nextAddr();

    ~Resolver();
};

#endif  // RESOLVER_H_
