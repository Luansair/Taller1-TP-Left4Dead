#ifndef ACTION_STARTCHANGE_H
#define ACTION_STARTCHANGE_H

#include "../information.h"

class StartChangeAction : public Information {

public:
    StartChangeAction() = default;

    [[nodiscard]] virtual std::vector<int8_t> serialize() const override;

    StartChangeAction(const StartChangeAction&) = delete;
    StartChangeAction& operator=(const StartChangeAction&) = delete;

    ~StartChangeAction() override = default;
};

#endif  // ACTION_STARTCHANGE_H
