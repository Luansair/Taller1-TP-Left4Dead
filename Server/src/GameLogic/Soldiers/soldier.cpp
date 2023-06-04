#include "../../../include/GameLogic/Soldiers/soldier.h"

Soldier::Soldier(
    int8_t dir,
    int8_t width,
    int8_t height,
    int8_t speed,
    int16_t health,
    std::unique_ptr<Weapon>&& weapon,
    std::unique_ptr<Grenade>&& grenade) :
    dir(dir),
    speed(speed),
    health(health),
    width(width),
    height(height),
    position(),
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
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies) {

    int16_t next_x;
    int16_t next_y;
    Hitbox hitbox;

    // calculo proxima coordenada.
    switch(axis) {
        case X:
            next_x = position.getXPos() + (dir * speed * time);
            next_y = position.getYPos();
            if (next_x < 0) next_x = width / 2;
            if (dir == RIGHT) {
                hitbox.setValues(position.getXPos(), next_x + width / 2, position.getYPos() - height / 2, position.getYPos() + height / 2);
            } else {
                hitbox.setValues(next_x - width / 2, position.getXPos(), position.getYPos() - height / 2, position.getYPos() + height / 2);
            }
            break;
        case Y:
            next_y = position.getYPos() + (dir * speed * time);
            next_x = position.getXPos();
            if (next_y < 0) next_y = height / 2;
            if (dir == UP) {
                hitbox.setValues(position.getXPos() - width / 2, position.getXPos() + width / 2, position.getYPos(), next_y + height / 2);
            } else {
                hitbox.setValues(position.getXPos() - width / 2, position.getXPos() + width / 2, next_y - height / 2, position.getYPos());
            }
            break;
    }

    Position next_pos(next_x, next_y, position.getWidth(), position.getHeight());

    // verifico las colisiones.

    for (auto i = soldiers.begin(); i != soldiers.end(); i++) {
        Position other_pos = i->second->getPosition();
        if (hitbox.move_hits(other_pos)) {
            if (axis == X) {
                if (dir == RIGHT) {
                    next_pos.setXPos(other_pos.getXMin() - width / 2 - 1);
                    hitbox.setValues(position.getXPos(), other_pos.getXMin() - 1 , position.getYPos() - height / 2, position.getYPos() + height / 2);
                } else if (dir == LEFT) {
                    next_pos.setXPos(other_pos.getXMax() + width / 2 + 1);
                    hitbox.setValues(other_pos.getXMax() + 1, position.getXPos(), position.getYPos() - height / 2, position.getYPos() + height / 2);
                }
            } else if (axis == Y) {
                if (dir == DOWN) {
                    next_pos.setYPos(other_pos.getYMax() + height / 2 + 1);
                    hitbox.setValues(position.getXPos() - width / 2, position.getXPos() + width / 2, position.getYPos(), other_pos.getYMax() + 1);
                } else if (dir == UP) {
                    next_pos.setYPos(other_pos.getYMin() - height / 2 - 1);
                    hitbox.setValues(position.getXPos() - width / 2, position.getXPos() + width / 2, other_pos.getYMin() - 1, position.getYPos());
                }
            }
        }
    }

    // lo mismo con los zombies

    // cambio de pos
    position = next_pos;

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
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies) {
    weapon->shoot(getPosition(), dir, time, std::ref(soldiers), std::ref(zombies));
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
    weapon->reload();
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

int8_t Soldier::getDir(void) {
    return dir;
}

int8_t Soldier::getHealth(void) {
    return health;
}

Position& Soldier::getPosition(void) {
    return std::ref(position);
}

const Position& Soldier::seePosition(void) const {
    return std::ref(position);
}

void Soldier::setPosition(Position&& new_pos) {
    position = new_pos;
}

uint8_t Soldier::getWidth(void) {
    return width;
}
uint8_t Soldier::getHeight(void) {
    return height;
}

bool Distance_from_left_is_minor::operator()(std::shared_ptr<Soldier> below, std::shared_ptr<Soldier> above)
    {
        if (below->getPosition().getXPos() > above->seePosition().getXPos()) {
            return true;
        }
 
        return false;
    }

bool Distance_from_right_is_minor::operator()(std::shared_ptr<Soldier> below, std::shared_ptr<Soldier> above)
    {
        if (below->seePosition().getXPos() < above->seePosition().getXPos()) {
            return true;
        }
 
        return false;
    }
