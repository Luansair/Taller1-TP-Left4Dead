#ifndef TP_ANIMATION_SOLDIER2_H
#define TP_ANIMATION_SOLDIER2_H

#include "../animation_action.h"
#include "animation_actor.h"

class SoldierTwoAnimation : public ActorAnimation {
    std::array<ActionAnimation, 10> animations;

public:
    explicit SoldierTwoAnimation(SDL2pp::Renderer& renderer);

    void draw(std::uint8_t animation_index, std::uint8_t *sprite_index, std::uint8_t direction,
              const SDL2pp::Point &sprite_destination, std::uint32_t frame_ticks) override;

    // Should not move because it can affect performance!
    SoldierTwoAnimation(SoldierTwoAnimation&&) = delete;
    SoldierTwoAnimation& operator=(SoldierTwoAnimation&&) = delete;

    SoldierTwoAnimation(const SoldierTwoAnimation&) = delete;
    SoldierTwoAnimation& operator=(const SoldierTwoAnimation&) = delete;

    ~SoldierTwoAnimation() override = default;
};

#endif //TP_ANIMATION_SOLDIER2_H
