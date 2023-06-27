#include "../../../include/Animations/Actor/animation_witch.h"

constexpr int zombie_width = 96;
constexpr int zombie_height = 96;

WitchAnimation::WitchAnimation(SDL2pp::Renderer &renderer) :
    animations{
            ActionAnimation(renderer, RESOURCES_PATH "/Witch/Attack_1.png",
                            loopable, zombie_width, zombie_height, 100),
            ActionAnimation(renderer, RESOURCES_PATH "/Witch/Attack_2.png",
                            loopable, zombie_width, zombie_height, 100),
            ActionAnimation(renderer, RESOURCES_PATH "/Witch/Attack_3.png",
                            loopable, zombie_width, zombie_height, 100),
            ActionAnimation(renderer, RESOURCES_PATH "/Witch/Dead.png",
                            no_loopable, zombie_width, zombie_height, 100),
            ActionAnimation(renderer, RESOURCES_PATH "/Witch/Hurt.png",
                            loopable, zombie_width, zombie_height, 100),
            ActionAnimation(renderer, RESOURCES_PATH "/Witch/Idle.png",
                            loopable, zombie_width, zombie_height, 200),
            ActionAnimation(renderer, RESOURCES_PATH "/Witch/Jump.png",
                            loopable, zombie_width, zombie_height, 100),
            ActionAnimation(renderer, RESOURCES_PATH "/Witch/Run.png",
                            loopable, zombie_width, zombie_height, 100),
            ActionAnimation(renderer, RESOURCES_PATH "/Witch/Scream.png",
                            loopable, zombie_width, zombie_height, 300),
            ActionAnimation(renderer, RESOURCES_PATH "/Witch/Walk.png",
                            loopable, zombie_width, zombie_height, 100)}{
}

void
WitchAnimation::draw(std::uint8_t animation_index, std::uint8_t *sprite_index, std::uint8_t direction,
                     const SDL2pp::Point &sprite_destination, std::uint32_t frame_ticks) {
    ActionAnimation& animation_to_draw = animations.at(animation_index);
    animation_to_draw.draw(sprite_index, direction, sprite_destination, frame_ticks);
}
