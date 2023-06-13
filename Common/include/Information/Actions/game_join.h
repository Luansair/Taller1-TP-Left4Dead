#ifndef ACTION_JOINGAME_H
#define ACTION_JOINGAME_H

#include "../information.h"

class JoinGameAction : public Information {
public:
    const uint32_t game_code;

    explicit JoinGameAction(uint32_t game_code);
    explicit JoinGameAction(const std::vector<int8_t>&
            serialized_bigendian_game_code);

    [[nodiscard]] virtual std::vector<int8_t> serialize() const override;

    ~JoinGameAction() = default;
};

#endif  // ACTION_JOINGAME_H
