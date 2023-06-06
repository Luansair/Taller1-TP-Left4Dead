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
              unsigned int frame_ticks,
              std::uint8_t direction,
              const SDL2pp::Rect& sprite_destination) override;

    ~SoldierOneAnimation() = default;
};

#endif //TP_ANIMATION_SOLDIER1_H
