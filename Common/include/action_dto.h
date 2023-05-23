#ifndef ACTIONDTO_H_
#define ACTIONDTO_H_

#include <cstdint>
#include <vector>

class Action {
protected:
    const std::uint8_t action_id;
public:
    explicit Action(std::uint8_t id);
    [[nodiscard]] virtual std::vector<int8_t> serialize() const
    = 0;

};

class ShootAction : public Action {
    const std::uint8_t shooting;

public:
    explicit ShootAction(std::uint8_t shooting);
    [[nodiscard]] virtual std::vector<int8_t> serialize() const override;
};

#endif  // ACTIONDTO_H_
