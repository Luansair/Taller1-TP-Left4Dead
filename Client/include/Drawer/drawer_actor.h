//
// Created by luan on 06/06/23.
//

#ifndef TP_DRAW_ACTOR_H
#define TP_DRAW_ACTOR_H

#include "../Animations/animation_manager.h"
#include "../../../Common/include/Information/state_dto_element.h"

// La ventaja de tener SoldierOneDrawer con un action específico Drawer es
// cada action drawer puede guardar un estado distinto!
class ActorDrawer {
    AnimationManager& animation_manager;
    std::uint8_t type;
    std::uint8_t animation;
    // std::uint8_t sprite_index;
    std::uint8_t direction;
    SDL2pp::Rect sprite_destination;

public:
    explicit ActorDrawer(AnimationManager& animation_manager);

    // Necesito saber la cantidad de sprites para mandar un indice válido!
    void updateInfo(const ElementStateDTO& actor_state);
    void draw(unsigned int frame_ticks);
};


#endif //TP_DRAW_ACTOR_H
