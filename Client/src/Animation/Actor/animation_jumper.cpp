#include "../../../include/Animations/Actor/animation_jumper.h"

constexpr int zombie_width = 96;
constexpr int zombie_height = 96;

JumperAnimation::JumperAnimation(SDL2pp::Renderer &renderer) :
    animations{
            ActionAnimation(renderer, RESOURCES_PATH "/Jumper/Attack_1.png",
                            loopable, zombie_width, zombie_height),
             ActionAnimation(renderer, RESOURCES_PATH "/Jumper/Attack_2.png",
                             loopable, zombie_width, zombie_height),
             ActionAnimation(renderer, RESOURCES_PATH "/Jumper/Attack_3.png",
                             loopable, zombie_width, zombie_height),
             ActionAnimation(renderer, RESOURCES_PATH "/Jumper/Dead.png",
                             no_loopable, zombie_width, zombie_height),
             ActionAnimation(renderer, RESOURCES_PATH "/Jumper/Eating.png",
                             loopable, zombie_width, zombie_height),
             ActionAnimation(renderer, RESOURCES_PATH "/Jumper/Hurt.png",
                             loopable, zombie_width, zombie_height),
             ActionAnimation(renderer, RESOURCES_PATH "/Jumper/Idle.png",
                             loopable, zombie_width, zombie_height),
             ActionAnimation(renderer, RESOURCES_PATH "/Jumper/Jump.png",
                             loopable, zombie_width, zombie_height),
             ActionAnimation(renderer, RESOURCES_PATH "/Jumper/Run.png",
                             loopable, zombie_width, zombie_height),
             ActionAnimation(renderer, RESOURCES_PATH "/Jumper/Walk.png",
                             loopable, zombie_width, zombie_height)}{
}

void
JumperAnimation::draw(std::uint8_t animation_index, std::uint8_t *sprite_index,
                      std::uint8_t direction,
                      const SDL2pp::Rect &sprite_destination) {
    ActionAnimation& animation_to_draw = animations.at(animation_index);
    animation_to_draw.draw(sprite_index, direction, sprite_destination);
}
