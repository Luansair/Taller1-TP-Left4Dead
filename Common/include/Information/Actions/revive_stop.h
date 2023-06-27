#ifndef ACTION_STOPREVIVE_H
#define ACTION_STOPREVIVE_H

#include "../information.h"

class StopReviveAction : public Information {

public:
    StopReviveAction() = default;

    [[nodiscard]] virtual std::vector<int8_t> serialize() const override;

    StopReviveAction(const StopReviveAction&) = delete;
    StopReviveAction& operator=(const StopReviveAction&) = delete;

    ~StopReviveAction() override = default;
};

#endif  // ACTION_STOPREVIVE_H
