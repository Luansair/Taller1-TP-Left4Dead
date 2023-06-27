#ifndef TP_ANIMATION_VENOM_H
#define TP_ANIMATION_VENOM_H

#include "../animation_action.h"
#include "animation_actor.h"

class VenomAnimation : public ActorAnimation {
    std::array<ActionAnimation, 9> animations;

public:
    explicit VenomAnimation(SDL2pp::Renderer& renderer);

    void draw(std::uint8_t animation_index, std::uint8_t *sprite_index, std::uint8_t direction,
              const SDL2pp::Point &sprite_destination, std::uint32_t frame_ticks) override;

    // Should not move because it can affect performance!
    VenomAnimation(VenomAnimation&&) = delete;
    VenomAnimation& operator=(VenomAnimation&&) = delete;

    VenomAnimation(const VenomAnimation&) = delete;
    VenomAnimation& operator=(const VenomAnimation&) = delete;

    ~VenomAnimation() override = default;
};
#endif //TP_ANIMATION_VENOM_H
