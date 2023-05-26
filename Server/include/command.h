#ifndef COMMAND_H_
#define COMMAND_H_

#include "../../Common/include/action_code.h"

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Command {
    public:
        virtual ~Command() {
        }
        virtual void Execute(void) const = 0;
};

class ShootCommand : public Command {
private:
    uint8_t player_id_;
    const vector<int8_t> &data;

public:
    explicit ShootCommand(uint8_t player_id, const vector<int8_t> &data);

    void Execute(void) const override;
};

class IdleCommand : public Command {
private:
    uint8_t player_id_;
    const vector<int8_t> &data;

public:
    explicit IdleCommand(uint8_t player_id, const vector<int8_t> &data);

    void Execute(void) const override;
};

class MoveCommand : public Command {
private:
    uint8_t player_id_;
    const vector<int8_t> &data;

public:
    explicit MoveCommand(uint8_t player_id, const vector<int8_t> &data);

    void Execute(void) const override;
};

class CgrenadeCommand : public Command {
private:
    uint8_t player_id_;
    const vector<int8_t> &data;

public:
    explicit CgrenadeCommand(uint8_t player_id, const vector<int8_t> &data);

    void Execute(void) const override;
};

class ReloadCommand : public Command {
private:
    uint8_t player_id_;
    const vector<int8_t> &data;

public:
    explicit ReloadCommand(uint8_t player_id, const vector<int8_t> &data);

    void Execute(void) const override;
};

class ThrowCommand : public Command {
private:
    uint8_t player_id_;
    const vector<int8_t> &data;

public:
    explicit ThrowCommand(uint8_t player_id, const vector<int8_t> &data);

    void Execute(void) const override;
};

class Factory {
public:
    Command* create(uint8_t player_id, const vector<int8_t> &data);
};

#endif  // COMMAND_H_
