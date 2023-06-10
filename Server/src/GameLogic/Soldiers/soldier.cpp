#include "../../../include/GameLogic/Soldiers/soldier.h"

Soldier::Soldier(
    uint32_t soldier_id,
    int8_t dir,
    int8_t width,
    int8_t height,
    int8_t speed,
    int16_t health,
    std::unique_ptr<Weapon>&& weapon,
    std::unique_ptr<Grenade>&& grenade) :
    soldier_id(soldier_id),
    dir(dir),
    speed(speed),
    health(health),
    width(width),
    height(height),
    position(),
    weapon(std::move(weapon)),
    grenade(std::move(grenade)) {
}

void Soldier::simulate(uint16_t time,
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies, int16_t dim_x, int16_t dim_y) {
    if (moving) simulateMove(time, soldiers, zombies, dim_x, dim_y);
    if (reloading) simulateReload(time);
    if (shooting) simulateShoot(time, soldiers, zombies);
    // simulateThrow(time, soldiers, zombies);
}

void Soldier::move(
    uint8_t state,
    uint8_t moveAxis,
    int8_t moveDirection,
    uint8_t moveForce) {

    switch(state) {
        case ON:
            moving = true;
            shooting = false;
            reloading = false;
            throwing = false;
            axis = moveAxis;
            dir = moveDirection;
            speed = moveForce;
            if (moveAxis == X) dir_x = moveDirection;
            break;
        case OFF:
            moving = false;
            break;
    }
}

void Soldier::simulateMove(uint16_t time,
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies, int16_t dim_x, int16_t dim_y) {

    // refactorizo simplificando el tema de la colisión, 
    // son tiempos tan chicos que si colisiono con algo directamente no me muevo
    // no uso hitbox, uso colisión entre posiciones y listo por el tema del mapa circular
    int16_t next_x;
    int16_t next_y;

    // calculo proxima coordenada.
    switch(axis) {
        case X:
            next_x = position.getXPos() + (dir * speed * time);
            next_y = position.getYPos();
            if (next_x < 0) next_x = dim_x + next_x;
            if (next_x > dim_x) next_x = next_x - dim_x;
            break;
        case Y:
            next_y = position.getYPos() + (dir * speed * time);
            next_x = position.getXPos();
            if (next_y < 0) next_y = dim_y + next_y;
            if (next_y > dim_y) next_y = next_y - dim_y;
            break;
    }

    Position next_pos(next_x, next_y, position.getWidth(), position.getHeight(), dim_x, dim_y);

    // verifico las colisiones.

    for (auto i = soldiers.begin(); i != soldiers.end(); i++) {
        Position other_pos = i->second->getPosition();
        if (i->second->getId() == soldier_id) continue;
        if (next_pos.collides(other_pos)) {
            return;
        }
    }

    // lo mismo con los zombies

    // si no colisiono cambio de pos
    position = next_pos;

}

void Soldier::shoot(uint8_t state) {
    switch(state) {
        case ON:
            shooting = true;
            moving = false;
            reloading = false;
            throwing = false;
            break;
        case OFF:
            shooting = false;
            break;
    }
}


void Soldier::simulateShoot(uint16_t time, 
    std::map<uint32_t, std::shared_ptr<Soldier>>& soldiers,
    std::map<uint32_t, std::shared_ptr<Zombie>>& zombies) {
    if (!(weapon->shoot(getPosition(), dir, time, std::ref(soldiers), std::ref(zombies)))) reload(ON);
}

void Soldier::reload(uint8_t state) {
    switch(state) {
        case ON:
            reloading = true;
            moving = false;
            shooting = false;
            throwing = false;
            break;
        case OFF:
            reloading = false;
            break;
    }
}

void Soldier::simulateReload(uint16_t time) {
    (weapon->reload());
}

void Soldier::throwGrenade(uint8_t state){
    switch(state) {
        case ON:
            throwing = true;
            moving = false;
            shooting = false;
            reloading = false;
            break;
        case OFF:
            throwing = false;
            break;
    }
    // grenade->throwg(x, y, dir);
}

void Soldier::simulateThrow(uint16_t time) {}

void Soldier::idle(uint8_t state) {
    switch(state) {
        case ON:
            reloading = false;
            shooting = false;
            moving = false;
            throwing = false;
            break;
        case OFF:
            break;
    }
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

int8_t Soldier::getDirX(void) {
    return dir_x;
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

uint32_t Soldier::getId(void) {
    return soldier_id;
}

uint8_t Soldier::getAction(void) {
    if (shooting) return ACTION_SHOOT;
    if (moving) return ACTION_MOVE;
    if (reloading) return ACTION_RELOAD;
    if (throwing) return ACTION_THROW;
    return ACTION_IDLE;
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
