//
// Created by luan on 06/06/23.
//
#include "../../include/Drawer/drawer_actor.h"
#include "../../include/Animations/animation_code.h"
#include "../../../Common/include/Information/information_code.h"

ActorDrawer::ActorDrawer(AnimationManager &animation_manager) :
        animation_manager(animation_manager),
        type(SOLDIER_1),
        animation(SOLDIER_1_IDLE),
        direction(DRAW_RIGHT),
        sprite_destination(0,0,128,128),
        sprite_index(0),
        previous_frame_ticks(0) {

}

// Paso sprite_index como puntero y si supera el tamaño me lo hace 0.
// Para que todos los jugadores vean las mismas animaciones, el server deberá
// enviar la animación específica, incluso si hay 3 tipos de ataques.
// Por ende la informacion de vuelta no es la misma que la de ida.
void ActorDrawer::updateInfo(const ElementStateDTO &actor_state) {
    if (this->animation != actor_state.action) {
        sprite_index = 0;
    }
    this->type = actor_state.type;
    this->animation = actor_state.action;
    this->direction = actor_state.direction;
    sprite_destination.SetX(actor_state.position_x);
    sprite_destination.SetY(actor_state.position_y);
}

void ActorDrawer::draw(unsigned int frame_ticks) {
    if (frame_ticks - previous_frame_ticks > 100) {
        sprite_index += 1;
        previous_frame_ticks = frame_ticks;
    }
    animation_manager.draw(type, animation, &sprite_index, direction,
                           sprite_destination);
}

