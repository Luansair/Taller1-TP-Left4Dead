#include "../../../include/GameLogic/Soldiers/soldier.h"

Soldier::Soldier(
    uint16_t x,
    uint16_t y,
    int8_t dir,
    uint8_t width,
    uint8_t height,
    uint8_t speed,
    uint16_t health,
    std::unique_ptr<Weapon>&& weapon,
    std::unique_ptr<Grenade>&& grenade) :
    x(x),
    y(y),
    dir(dir),
    width(width),
    height(height),
    speed(speed),
    health(health),
    weapon(std::move(weapon)),
    grenade(std::move(grenade)) {
}

void Soldier::simulateStep(uint16_t time) {}

void Soldier::move(
    uint8_t state,
    uint8_t moveAxis,
    int8_t moveDirection,
    uint8_t moveForce) {

    switch(state) {
        case ON:
            moving = true;
            axis = moveAxis;
            dir = moveDirection;
            speed = moveForce;
            break;
        case OFF:
            moving = false;
            break;
    }
}

void Soldier::simulateMove(uint16_t time,
    std::map<uint32_t, std::unique_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::unique_ptr<Zombie>>& zombies) {

    // calculo proxima coordenada.
    switch(axis) {
        case X:
            next_x = x + (dir * speed * time);
            next_y = y;
            break;
        case Y:
            next_y = y - (dir * speed * time);
            next_x = x;
            break;
    }

    // verifico las colisiones.

    for (auto i = soldiers.begin(); i != soldiers.end(); i++) {
        uint16_t x_other = i->second->getXPos();
        uint16_t y_other = i->second->getYPos();
        uint8_t width_other = i->second->getWidth();
        uint8_t height_other = i->second->getHeight();
        collides(x_other, y_other, width_other, height_other);
    }

    // lo mismo con los zombies

    // cambio de pos
    x = next_x;
    y = next_y;

}

void Soldier::collides(uint16_t x_other, uint16_t y_other, uint8_t width_other, uint8_t height_other) {
    uint16_t x_other_max = x_other + width_other;
    uint16_t x_other_min = x_other - width_other;
    uint16_t y_other_max = y_other + width_other;
    uint16_t y_other_min = y_other - width_other;
    uint16_t x_max = next_x + width;
    uint16_t x_min = next_x - width;
    uint16_t y_max = next_y + width;
    uint16_t y_min = next_y - width;

    if ((((x_other_min <= x_max) || (x_max <= x_other_max)) || (((x_other_min <= x_min) || (x_min <= x_other_max)))) && 
    (((y_other_min <= y_max) || (y_max <= y_other_max)) || (((y_other_min <= y_min) || (y_min <= y_other_max))))) {
        if (axis == X) {
            if (dir == RIGHT) {
                next_x = x_other_min;
            } else if (dir == LEFT) {
                next_x = x_other_max;
            }
        } else if (axis == Y) {
            if (dir == DOWN) {
                next_y = y_other_max;
            } else if (dir == UP) {
                next_y = y_other_min;
            }
        }
    }
}

void Soldier::shoot(uint8_t state) {
    switch(state) {
        case ON:
            shooting = true;
            break;
        case OFF:
            shooting = false;
            break;
    }
}


void Soldier::simulateShoot(uint16_t time, 
    std::map<uint32_t, std::unique_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::unique_ptr<Zombie>>& zombies) {
    // weapon->shoot(time, std::ref(soldiers), std::ref(zombies));
}

void Soldier::reload(uint8_t state) {
    switch(state) {
        case ON:
            reloading = true;
            break;
        case OFF:
            reloading = false;
            break;
    }
    // weapon->reload(state);
}

void Soldier::simulateReload(uint16_t time) {}

void Soldier::throwGrenade(uint8_t state){
    switch(state) {
        case ON:
            throwing = true;
            break;
        case OFF:
            throwing = false;
            break;
    }
    // grenade->throwg(x, y, dir);
}

void Soldier::simulateThrow(uint16_t time) {}

void Soldier::cGrenade(void) {
    // grenade_type = otra
}

void Soldier::recvDamage(int8_t damage) {
    if (damage < health) {
        health -= damage; 
        return;
    }
}

void Soldier::setPos(uint16_t new_x, uint16_t new_y, int8_t new_dir) {
    x = new_x;
    y = new_y;
    dir = new_dir;
}

uint16_t Soldier::getXPos(void) {
    return x;
}
uint16_t Soldier::getYPos(void) {
    return y;
}

int8_t Soldier::getDir(void) {
    return dir;
}

int8_t Soldier::getHealth(void) {
    return health;
}

uint8_t Soldier::getWidth(void) {
    return width;
}

uint8_t Soldier::getHeight(void) {
    return height;
}
