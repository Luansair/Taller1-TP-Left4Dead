#include "action.h"

#ifndef ACTION_JOINGAME_H
#define ACTION_JOINGAME_H

class JoinGameAction : public Action {
public:
    const uint32_t game_code;

    explicit JoinGameAction(uint32_t game_code);
    explicit JoinGameAction(const std::vector<int8_t>&
            serialized_bigendian_game_code);

    [[nodiscard]] virtual std::vector<int8_t> serialize() const override;

    ~JoinGameAction() override = default;
};

#endif  // ACTION_JOINGAME_H