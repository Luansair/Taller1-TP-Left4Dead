#ifndef ACTION_STOPTHROW_H
#define ACTION_STOPTHROW_H

#include "../information.h"

class StopThrowAction : public Information {

public:
    StopThrowAction() = default;

    [[nodiscard]] virtual std::vector<int8_t> serialize() const override;

    StopThrowAction(const StopThrowAction&) = delete;
    StopThrowAction& operator=(const StopThrowAction&) = delete;

    ~StopThrowAction() override = default;
};

#endif  // ACTION_STOPTHROW_H
