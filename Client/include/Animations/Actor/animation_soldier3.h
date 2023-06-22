#ifndef TP_ANIMATION_SOLDIER3_H
#define TP_ANIMATION_SOLDIER3_H

#include "../animation_action.h"
#include "animation_actor.h"

class SoldierThreeAnimation : public ActorAnimation {
    std::array<ActionAnimation, 11> animations;

public:
    explicit SoldierThreeAnimation(SDL2pp::Renderer& renderer);

    void draw(std::uint8_t animation_index,
              std::uint8_t *sprite_index,
              std::uint8_t direction,
              const SDL2pp::Point &sprite_destination) override;

    // Should not move because it can affect performance!
    SoldierThreeAnimation(SoldierThreeAnimation&&) = delete;
    SoldierThreeAnimation& operator=(SoldierThreeAnimation&&) = delete;

    SoldierThreeAnimation(const SoldierThreeAnimation&) = delete;
    SoldierThreeAnimation& operator=(const SoldierThreeAnimation&) = delete;

    ~SoldierThreeAnimation() override = default;
};

#endif //TP_ANIMATION_SOLDIER3_H
