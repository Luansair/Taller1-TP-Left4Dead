#ifndef ACTION_STARTRELOAD_H
#define ACTION_STARTRELOAD_H

#include "../information.h"

class StartReloadAction : public Information {

public:
    StartReloadAction() = default;

    [[nodiscard]] virtual std::vector<int8_t> serialize() const override;

    StartReloadAction(const StartReloadAction&) = delete;
    StartReloadAction& operator=(const StartReloadAction&) = delete;

    ~StartReloadAction() override = default;
};

#endif  // ACTION_STARTRELOAD_H
