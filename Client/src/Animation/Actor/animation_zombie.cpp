//
// Created by luan on 09/06/23.
//
#include "../../../include/Animations/Actor/animation_zombie.h"

ZombieAnimation::ZombieAnimation(SDL2pp::Renderer &renderer) :
    animations{
             ActionAnimation(renderer, RESOURCES_PATH "/Zombie/Attack_1.png",
                             loopable),
             ActionAnimation(renderer, RESOURCES_PATH "/Zombie/Attack_2.png",
                             loopable),
             ActionAnimation(renderer, RESOURCES_PATH "/Zombie/Attack_3.png",
                             loopable),
             ActionAnimation(renderer, RESOURCES_PATH "/Zombie/Bite.png",
                             loopable),
             ActionAnimation(renderer, RESOURCES_PATH "/Zombie/Dead.png",
                             no_loopable),
             ActionAnimation(renderer, RESOURCES_PATH "/Zombie/Hurt.png",
                             loopable),
             ActionAnimation(renderer, RESOURCES_PATH "/Zombie/Idle.png",
                             loopable),
             ActionAnimation(renderer, RESOURCES_PATH "/Zombie/Jump.png",
                             loopable),
             ActionAnimation(renderer, RESOURCES_PATH "/Zombie/Run.png",
                             loopable),
             ActionAnimation(renderer, RESOURCES_PATH "/Zombie/Walk.png",
                             loopable) }{
}

void
ZombieAnimation::draw(std::uint8_t animation_index, std::uint8_t *sprite_index,
                      std::uint8_t direction,
                      const SDL2pp::Rect &sprite_destination) {
    ActionAnimation& animation_to_draw = animations.at(animation_index);
    animation_to_draw.draw(sprite_index, direction, sprite_destination);
}

