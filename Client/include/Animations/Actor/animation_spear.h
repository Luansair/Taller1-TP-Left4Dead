#ifndef TP_ANIMATION_SPEAR_H
#define TP_ANIMATION_SPEAR_H

#include "../animation_action.h"
#include "animation_actor.h"

class SpearAnimation : public ActorAnimation {
    std::array<ActionAnimation, 10> animations;

public:
    explicit SpearAnimation(SDL2pp::Renderer& renderer);

    void draw(std::uint8_t animation_index, std::uint8_t *sprite_index, std::uint8_t direction,
              const SDL2pp::Point &sprite_destination, std::uint32_t frame_ticks) override;

    // Should not move because it can affect performance!
    SpearAnimation(SpearAnimation&&) = delete;
    SpearAnimation& operator=(SpearAnimation&&) = delete;

    SpearAnimation(const SpearAnimation&) = delete;
    SpearAnimation& operator=(const SpearAnimation&) = delete;

    ~SpearAnimation() override = default;
};
#endif //TP_ANIMATION_SPEAR_H
