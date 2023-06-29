#ifndef ACTION_STARTEXIT_H
#define ACTION_STARTEXIT_H

#include "../information.h"

class StartExitAction : public Information {

public:
    StartExitAction() = default;

    [[nodiscard]] virtual std::vector<int8_t> serialize() const override;

    StartExitAction(const StartExitAction&) = delete;
    StartExitAction& operator=(const StartExitAction&) = delete;

    ~StartExitAction() override = default;
};

#endif  // ACTION_STARTEXIT_H
