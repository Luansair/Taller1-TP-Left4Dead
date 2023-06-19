#include "../../../include/Animations/Actor/animation_soldier2.h"
#include "../../../include/Animations/LoopType/looptype_no_loopable.h"
#include "../../../include/Animations/LoopType/looptype_loopable.h"

// Would like to choose the position to put the animation in the array.
SoldierTwoAnimation::SoldierTwoAnimation(SDL2pp::Renderer &renderer) :
    animations{
            ActionAnimation(renderer, RESOURCES_PATH "/Soldier_2/Attack.png",
                            loopable, 128, 128),
     ActionAnimation(renderer, RESOURCES_PATH "/Soldier_2/Dead.png",
                     no_loopable, 128, 128),
     ActionAnimation(renderer, RESOURCES_PATH "/Soldier_2/Grenade.png",
                     loopable, 128, 128),
     ActionAnimation(renderer, RESOURCES_PATH "/Soldier_2/Hurt.png",
                     loopable, 128, 128),
     ActionAnimation(renderer, RESOURCES_PATH "/Soldier_2/Idle.png",
                     loopable, 128, 128),
     ActionAnimation(renderer, RESOURCES_PATH "/Soldier_2/Recharge.png",
                     no_loopable, 128, 128),
     ActionAnimation(renderer, RESOURCES_PATH "/Soldier_2/Run.png",
                     loopable, 128, 128),
     ActionAnimation(renderer, RESOURCES_PATH "/Soldier_2/Shot_1.png",
                     loopable, 128, 128),
     ActionAnimation(renderer, RESOURCES_PATH "/Soldier_2/Shot_2.png",
                     loopable, 128, 128),
     ActionAnimation(renderer, RESOURCES_PATH "/Soldier_2/Walk.png",
                     loopable, 128, 128)} {
}

void SoldierTwoAnimation::draw(std::uint8_t animation_index,
                               std::uint8_t *sprite_index,
                               std::uint8_t direction,
                               const SDL2pp::Rect &sprite_destination) {

    ActionAnimation& animation_to_draw = animations.at(animation_index);
    animation_to_draw.draw(sprite_index, direction, sprite_destination);
}
