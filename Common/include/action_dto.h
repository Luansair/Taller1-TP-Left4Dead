#ifndef ACTIONDTO_H_
#define ACTIONDTO_H_

#include <cstdint>
#include <vector>

class Action {

public:
    Action() = default;
    [[nodiscard]] virtual std::vector<int8_t> serialize() const
    = 0;

    Action(Action&&) = default;
    Action& operator=(Action&&) = default;

    virtual ~Action() = default;
};

class StartShootAction : public Action {

public:
    StartShootAction() = default;
    [[nodiscard]] virtual std::vector<int8_t> serialize() const override;

    ~StartShootAction() override = default;
};

class CreateGameAction : public Action {

public:
    CreateGameAction() = default;
    [[nodiscard]] virtual std::vector<int8_t> serialize() const override;

    ~CreateGameAction() override = default;
};

class JoinGameAction : public Action {
    uint32_t game_code;
public:
    explicit JoinGameAction(uint32_t game_code);
    [[nodiscard]] virtual std::vector<int8_t> serialize() const override;

    ~JoinGameAction() override = default;
};

#endif  // ACTIONDTO_H_
