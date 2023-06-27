#ifndef ACTION_JOINGAME_H
#define ACTION_JOINGAME_H

#include "../information.h"

class JoinGameAction : public Information {
public:
    const uint32_t game_code;

    explicit JoinGameAction(uint32_t game_code);
    explicit JoinGameAction(const std::vector<int8_t>&
            serialized_bigendian_game_code);

    [[nodiscard]] std::vector<int8_t> serialize() const override;

    JoinGameAction(const JoinGameAction&) = delete;
    JoinGameAction& operator=(const JoinGameAction&) = delete;

    ~JoinGameAction() override = default;
};

#endif  // ACTION_JOINGAME_H
