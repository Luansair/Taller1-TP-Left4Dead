#include "../../../include/Animations/Actor/animation_spear.h"

constexpr int zombie_width = 128;
constexpr int zombie_height = 128;

SpearAnimation::SpearAnimation(SDL2pp::Renderer &renderer) :
    animations{
            ActionAnimation(renderer, RESOURCES_PATH "/Spear/Attack_1.png",
                            loopable, zombie_width, zombie_height, 100),
            ActionAnimation(renderer, RESOURCES_PATH "/Spear/Attack_2.png",
                            loopable, zombie_width, zombie_height, 100),
            ActionAnimation(renderer, RESOURCES_PATH "/Spear/Dead.png",
                            no_loopable, zombie_width, zombie_height, 100),
            ActionAnimation(renderer, RESOURCES_PATH "/Spear/Fall.png",
                            loopable, zombie_width, zombie_height, 100),
            ActionAnimation(renderer, RESOURCES_PATH "/Spear/Hurt.png",
                            loopable, zombie_width, zombie_height, 100),
            ActionAnimation(renderer, RESOURCES_PATH "/Spear/Idle.png",
                            loopable, zombie_width, zombie_height, 200),
            ActionAnimation(renderer, RESOURCES_PATH "/Spear/Protect.png",
                            loopable, zombie_width, zombie_height, 100),
            ActionAnimation(renderer, RESOURCES_PATH "/Spear/Run.png",
                            loopable, zombie_width, zombie_height, 100),
            ActionAnimation(renderer, RESOURCES_PATH "/Spear/Run+attack.png",
                            loopable, zombie_width, zombie_height, 100),
            ActionAnimation(renderer, RESOURCES_PATH "/Spear/Walk.png",
                            loopable, zombie_width, zombie_height, 100)}{
}

void
SpearAnimation::draw(std::uint8_t animation_index, std::uint8_t *sprite_index, std::uint8_t direction,
                     const SDL2pp::Point &sprite_destination, std::uint32_t frame_ticks) {
    ActionAnimation& animation_to_draw = animations.at(animation_index);
    animation_to_draw.draw(sprite_index, direction, sprite_destination, frame_ticks);
}
