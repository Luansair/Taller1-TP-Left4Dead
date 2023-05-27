#include "../../include/Command/command.h"

ShootCommand::ShootCommand(uint8_t player_id, const vector<int8_t> &data) : 
    player_id_(player_id),
    data(data) {
    }

void ShootCommand::Execute(void) const {
    // int8_t state = data[1];
    // game.shoot(player_id_, state);
}

MoveCommand::MoveCommand(uint8_t player_id, const vector<int8_t> &data) : 
    player_id_(player_id),
    data(data) {
    }

void MoveCommand::Execute(void) const {
}

IdleCommand::IdleCommand(uint8_t player_id, const vector<int8_t> &data) : 
    player_id_(player_id),
    data(data) {
    }

void IdleCommand::Execute(void) const {
}

ReloadCommand::ReloadCommand(uint8_t player_id, const vector<int8_t> &data) : 
    player_id_(player_id),
    data(data) {
    }

void ReloadCommand::Execute(void) const {
}

CgrenadeCommand::CgrenadeCommand(uint8_t player_id, const vector<int8_t> &data) : 
    player_id_(player_id),
    data(data) {
    }

void CgrenadeCommand::Execute(void) const {
}

ThrowCommand::ThrowCommand(uint8_t player_id, const vector<int8_t> &data) : 
    player_id_(player_id),
    data(data) {
    }

void ThrowCommand::Execute(void) const {
}

Command* Factory::create(uint8_t player_id, const vector<int8_t> &data) {
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
