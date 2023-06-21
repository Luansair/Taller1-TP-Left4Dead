#ifndef TP_ANIMATION_WITCH_H
#define TP_ANIMATION_WITCH_H

#include "../animation_action.h"
#include "animation_actor.h"

class WitchAnimation : public ActorAnimation {
    std::array<ActionAnimation, 10> animations;

public:
    explicit WitchAnimation(SDL2pp::Renderer& renderer);

    void draw(std::uint8_t animation_index,
              std::uint8_t *sprite_index,
              std::uint8_t direction,
              const SDL2pp::Rect& sprite_destination) override;

    // Should not move because it can affect performance!
    WitchAnimation(WitchAnimation&&) = delete;
    WitchAnimation& operator=(WitchAnimation&&) = delete;

    WitchAnimation(const WitchAnimation&) = delete;
    WitchAnimation& operator=(const WitchAnimation&) = delete;

    ~WitchAnimation() override = default;
};
#endif //TP_ANIMATION_WITCH_H
