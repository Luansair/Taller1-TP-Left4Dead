#include "../../include/Command/command.h"

JoinCommand::JoinCommand(uint8_t player_id, const std::vector<int8_t> &data) : 
    player_id_(player_id),
    data(data) {
    }

void JoinCommand::Execute(Match &match) const {
    int8_t soldier_type = data[1];
    match.join(player_id_, soldier_type);
}

ShootCommand::ShootCommand(uint8_t player_id, const std::vector<int8_t> &data) : 
    player_id_(player_id),
    data(data) {
    }

void ShootCommand::Execute(Match &match) const {
    int8_t state = data[1];
    match.shoot(player_id_, state);
}

MoveCommand::MoveCommand(uint8_t player_id, const std::vector<int8_t> &data) : 
    player_id_(player_id),
    data(data) {
    }

void MoveCommand::Execute(Match &match) const {
    uint8_t state = data[1];
    uint8_t moveAxis = data[2];
    int8_t moveDirection = data[3];
    uint8_t moveForce = data[4];
    match.move(player_id_, state, moveAxis, moveDirection, moveForce);
}

IdleCommand::IdleCommand(uint8_t player_id, const std::vector<int8_t> &data) : 
    player_id_(player_id),
    data(data) {
    }

void IdleCommand::Execute(Match &match) const {
    match.idle(player_id_);
}

ReloadCommand::ReloadCommand(uint8_t player_id, const std::vector<int8_t> &data) : 
    player_id_(player_id),
    data(data) {
    }

void ReloadCommand::Execute(Match &match) const {
    int8_t state = data[1];
    match.reload(player_id_, state);
}

CgrenadeCommand::CgrenadeCommand(uint8_t player_id, const std::vector<int8_t> &data) : 
    player_id_(player_id),
    data(data) {
    }

void CgrenadeCommand::Execute(Match &match) const {
    match.cGrenade(player_id_);
}

ThrowCommand::ThrowCommand(uint8_t player_id, const std::vector<int8_t> &data) : 
    player_id_(player_id),
    data(data) {
    }

void ThrowCommand::Execute(Match &match) const {
    match.throwGrenade(player_id_);
}

Command* CommandFactory::create(uint8_t player_id, const std::vector<int8_t> &data) {
    switch(data[0])
    {
        case IDLE:
            return new IdleCommand(player_id, data);
        case SHOOT:
            return new ShootCommand(player_id, data);
        case MOVE:
            return new MoveCommand(player_id, data);
        case RELOAD:
            return new ReloadCommand(player_id, data);
        case CHANGE_GRENADE:
            return new CgrenadeCommand(player_id, data);
        case THROW:
            return new ThrowCommand(player_id, data);
    }
    return new IdleCommand(player_id, data); // no se que devolver en caso de error
}
