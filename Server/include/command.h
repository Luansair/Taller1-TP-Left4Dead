#ifndef COMMAND_H_
#define COMMAND_H_

#include "game.h"

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Command {
    public:
        virtual ~Command() {
        }
        virtual void Execute() const = 0;
};

class ShootCommand : public Command {
private:
    uint_8 player_id_;
    vector<int8_t> data;

public:
    explicit ShootCommand(uint_8 player_id, vector<int8_t> data);

    void Execute(Game &game) const override;
};

class IdleCommand : public Command {
private:
    uint_8 player_id_;
    vector<int8_t> data;

public:
    explicit IdleCommand(uint_8 player_id, vector<int8_t> data);

    void Execute(Game &game) const override;
};

class MoveCommand : public Command {
private:
    uint_8 player_id_;
    vector<int8_t> data;

public:
    explicit MoveCommand(uint_8 player_id, vector<int8_t> data);

    void Execute(Game &game) const override;
};

class CgrenadeCommand : public Command {
private:
    uint_8 player_id_;
    vector<int8_t> data;

public:
    explicit CgrenadeCommand(uint_8 player_id, vector<int8_t> data);

    void Execute(Game &game) const override;
};

class ReloadCommand : public Command {
private:
    uint_8 player_id_;
    vector<int8_t> data;

public:
    explicit ReloadCommand(uint_8 player_id, vector<int8_t> data);

    void Execute(Game &game) const override;
};

class ThrowCommand : public Command {
private:
    uint_8 player_id_;
    vector<int8_t> data;

public:
    explicit ThrowCommand(uint_8 player_id, vector<int8_t> data);

    void Execute(Game &game) const override;
};

class Factory {
public:
    Command* create(Game &game, uint_8 player_id, vector<int8_t> data);
};

#endif  // COMMAND_H_
