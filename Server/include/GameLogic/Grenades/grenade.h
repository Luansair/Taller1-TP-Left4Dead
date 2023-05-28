#ifndef GRENADE_H_
#define GRENADE_H_

#include <cstdint>
#include <utility>

class Grenade {
public:
    virtual ~Grenade() {}
    virtual void throwg(void) = 0;
};

#endif  // GRENADE_H_
