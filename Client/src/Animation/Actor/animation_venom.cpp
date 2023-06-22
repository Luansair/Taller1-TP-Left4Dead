#include "../../../include/Animations/Actor/animation_venom.h"

constexpr int zombie_width = 128;
constexpr int zombie_height = 128;

VenomAnimation::VenomAnimation(SDL2pp::Renderer &renderer) :
    animations{
            ActionAnimation(renderer, RESOURCES_PATH "/Venom/Attack1.png",
                            loopable, zombie_width, zombie_height),
            ActionAnimation(renderer, RESOURCES_PATH "/Venom/Attack1a.png",
                            loopable, zombie_width, zombie_height),
             ActionAnimation(renderer, RESOURCES_PATH "/Venom/Attack2.png",
                             loopable, zombie_width, zombie_height),
             ActionAnimation(renderer, RESOURCES_PATH "/Venom/Dead.png",
                             no_loopable, zombie_width, zombie_height),
             ActionAnimation(renderer, RESOURCES_PATH "/Venom/Hurt.png",
                             loopable, zombie_width, zombie_height),
             ActionAnimation(renderer, RESOURCES_PATH "/Venom/Idle.png",
                             loopable, zombie_width, zombie_height),
             ActionAnimation(renderer, RESOURCES_PATH "/Venom/Jump.png",
                             loopable, zombie_width, zombie_height),
             ActionAnimation(renderer, RESOURCES_PATH "/Venom/Run.png",
                             loopable, zombie_width, zombie_height),
             ActionAnimation(renderer, RESOURCES_PATH "/Venom/Walk.png",
                             loopable, zombie_width, zombie_height)}{
}

void
VenomAnimation::draw(std::uint8_t animation_index, std::uint8_t *sprite_index,
                     std::uint8_t direction,
                     const SDL2pp::Point &sprite_destination) {
    ActionAnimation& animation_to_draw = animations.at(animation_index);
    animation_to_draw.draw(sprite_index, direction, sprite_destination);
}
