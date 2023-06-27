#ifndef ACTION_STOPRELOAD_H
#define ACTION_STOPRELOAD_H

#include "../information.h"

class StopReloadAction : public Information {

public:
    StopReloadAction() = default;

    [[nodiscard]] virtual std::vector<int8_t> serialize() const override;

    StopReloadAction(const StopReloadAction&) = delete;
    StopReloadAction& operator=(const StopReloadAction&) = delete;

    ~StopReloadAction() override = default;
};

#endif  // ACTION_STOPRELOAD_H
