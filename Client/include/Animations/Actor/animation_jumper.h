#ifndef TP_ANIMATION_JUMPER_H
#define TP_ANIMATION_JUMPER_H

#include "../animation_action.h"
#include "animation_actor.h"

class JumperAnimation : public ActorAnimation {
    std::array<ActionAnimation, 10> animations;

public:
    explicit JumperAnimation(SDL2pp::Renderer& renderer);

    void draw(std::uint8_t animation_index,
              std::uint8_t *sprite_index,
              std::uint8_t direction,
              const SDL2pp::Rect& sprite_destination) override;

    // Should not move because it can affect performance!
    JumperAnimation(JumperAnimation&&) = delete;
    JumperAnimation& operator=(JumperAnimation&&) = delete;

    JumperAnimation(const JumperAnimation&) = delete;
    JumperAnimation& operator=(const JumperAnimation&) = delete;

    ~JumperAnimation() override = default;
};
#endif //TP_ANIMATION_JUMPER_H
