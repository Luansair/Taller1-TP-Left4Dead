#ifndef COLLISIONZONE_H_
#define COLLISIONZONE_H_

#include <string>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <map>
#include <vector>
#include <memory>
using namespace std;

class Soldier;
class Zombie;

class CollisionZone {
private:
    bool occupied;
    Soldier* soldier = nullptr;
    // Crater crater;

public:
    CollisionZone(void);

    void executeCollision(uint8_t damage);

    bool is_occupied(void);

    void occupy(Soldier* soldier);

    void vacate(void);

    CollisionZone(const CollisionZone&) = delete;
    CollisionZone& operator=(const CollisionZone&) = delete;
};

#endif  // COLLISIONZONE_H_
