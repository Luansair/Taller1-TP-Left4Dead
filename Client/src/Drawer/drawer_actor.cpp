//
// Created by luan on 06/06/23.
//
#include "../../include/Drawer/drawer_actor.h"
#include "../../include/Animations/animation_code.h"
#include "../../../Common/include/Information/information_code.h"

constexpr std::int16_t TOLERANCE = 200;

ActorDrawer::ActorDrawer(AnimationManager &animation_manager) :
        animation_manager(animation_manager),
        type(SOLDIER_IDF),
        animation(SOLDIER_1_IDLE),
        direction(DRAW_RIGHT),
        sprite_destination(0,0),
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
    // se congela la animación, si le mando directamente desde server sin traducir anda bien.
    //setActorType(actor_state.type);
    this->type = actor_state.type;
    this->animation = actor_state.action;
    //setActorAnimation(actor_state.action);
    setActorDirection(actor_state.direction);
    this->position_x = actor_state.position_x;
    this->position_y = actor_state.position_y;
}

void ActorDrawer::draw(std::uint32_t frame_ticks, std::int32_t window_x_pos, std::int32_t window_width) {
    if (frame_ticks - previous_frame_ticks > 100) {
        sprite_index += 1;
        previous_frame_ticks = frame_ticks;
    }

    std::int32_t actor_x_pos = position_x;
    std::int32_t relative_x_pos_to_window = actor_x_pos - window_x_pos;

    if (relative_x_pos_to_window < -TOLERANCE || relative_x_pos_to_window > window_width + TOLERANCE) {
        return;
    }

    animation_manager.draw(type, animation, &sprite_index, direction,
                           {relative_x_pos_to_window, position_y});
}


void ActorDrawer::setActorDirection(int8_t actor_direction) {
    switch (actor_direction)
    {
    case RIGHT:
        this->direction = DRAW_RIGHT;
        break;
    
    case LEFT:
        this->direction = DRAW_LEFT;
        break;
    }
}
