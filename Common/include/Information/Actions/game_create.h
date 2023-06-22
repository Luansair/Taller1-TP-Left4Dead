#ifndef ACTION_CREATEGAME_H
#define ACTION_CREATEGAME_H

#include "../information.h"

class CreateGameAction : public Information {

public:
    uint8_t gameMode;
    explicit CreateGameAction(uint8_t mode);

    [[nodiscard]] std::vector<int8_t> serialize() const override;

    CreateGameAction(const CreateGameAction&) = delete;
    CreateGameAction& operator=(const CreateGameAction&) = delete;

    ~CreateGameAction() override = default;
};

#endif  // ACTION_CREATEGAME_H
