#include "../include/command.h"

ShootCommand::ShootCommand(uint_8 player_id, vector<int8_t> data) : 
    player_id_(player_id),
    data_(data) {
    }

void ShootCommand::Execute(Game &game) const {
    // int8_t state = data[1];
    // game.shoot(player_id_, state);
}

MoveCommand::MoveCommand(uint_8 player_id, vector<int8_t> data) : 
    player_id_(player_id),
    data_(data) {
    }

void MoveCommand::Execute(Game &game) const {
}

IdleCommand::IdleCommand(uint_8 player_id, vector<int8_t> data) : 
    player_id_(player_id),
    data_(data) {
    }

void IdleCommand::Execute(Game &game) const {
}

ReloadCommand::ReloadCommand(uint_8 player_id, vector<int8_t> data) : 
    player_id_(player_id),
    data_(data) {
    }

void ReloadCommand::Execute(Game &game) const {
}

CgrenadeCommand::CgrenadeCommand(uint_8 player_id, vector<int8_t> data) : 
    player_id_(player_id),
    data_(data) {
    }

void CgrenadeCommand::Execute(Game &game) const {
}

ThrowCommand::ThrowCommand(uint_8 player_id, vector<int8_t> data) : 
    player_id_(player_id),
    data_(data) {
    }

void ThrowCommand::Execute(Game &game) const {
}

Command* Factory::create(Game &game, uint_8 player_id, vector<int8_t> data) {
    switch(data[0])
    {
        case IDLE:
            return new IdleCommand(game, player_id, data);
        case SHOOT:
            return new ShootCommand(game, player_id, data);
        case MOVE:
            return new MoveCommand(game, player_id, data);
        case RELOAD:
            return new ReloadCommand(game, player_id, data);
        case CHANGE_GRENADE:
            return new CgrenadeCommand(game, player_id, data);
        case THROW:
            return new ThrowCommand(game, player_id, data);
    }
}
