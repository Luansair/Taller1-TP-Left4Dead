//
// Created by luan on 06/06/23.
//

#ifndef TP_ANIMATION_SOLDIER1_H
#define TP_ANIMATION_SOLDIER1_H

#include "animation_action.h"
#include "animation_actor.h"

class SoldierOneAnimation : public ActorAnimation {
    std::array<ActionAnimation, 11> animations;

public:
    explicit SoldierOneAnimation(SDL2pp::Renderer& renderer);

    void draw(std::uint8_t animation_index,
              std::uint8_t *sprite_index,
              std::uint8_t direction,
              const SDL2pp::Rect& sprite_destination) override;

    // Should not move because it can affect performance!
    SoldierOneAnimation(SoldierOneAnimation&&) = delete;
    SoldierOneAnimation& operator=(SoldierOneAnimation&&) = delete;

    SoldierOneAnimation(const SoldierOneAnimation&) = delete;
    SoldierOneAnimation& operator=(const SoldierOneAnimation&) = delete;

    ~SoldierOneAnimation() override = default;
};

#endif //TP_ANIMATION_SOLDIER1_H
