//
// Created by luan on 06/06/23.
//
#include "../../include/Drawer/drawer_actor.h"
#include "../../include/Animations/animation_code.h"
#include "../../../Common/include/Information/information_code.h"

constexpr std::int16_t TOLERANCE = 200;
constexpr float ROAD_RATIO = 0.150;
constexpr float SV_MAP_HEIGHT = 200;

ActorDrawer::ActorDrawer(AnimationManager &animation_manager, SDL2pp::Renderer &renderer) :
        animation_manager(animation_manager),
        hp_drawer(renderer),
        type(SOLDIER_IDF),
        animation(SOLDIER_1_IDLE),
        direction(DRAW_RIGHT),
        ammo(0),
        actual_ammo(0),
        timeleft(0),
        sprite_destination(0,0),
        drawable(false),
        sprite_index(0),
        previous_frame_ticks(0) {

}

// Paso sprite_index como puntero y si supera el tamaño me lo hace 0.
// Para que todos los jugadores vean las mismas animaciones, el server deberá
// enviar la animación específica, incluso si hay 3 tipos de ataques.
// Por ende la informacion de vuelta no es la misma que la de ida.
void
ActorDrawer::updateInfo(const ElementStateDTO &actor_state, std::int32_t window_x_pos, std::int32_t window_width,
                        std::int32_t window_height) {
    if (this->animation != actor_state.action) {
        sprite_index = 0;
    }
    this->type = actor_state.type;
    this->animation = actor_state.action;
    setActorDirection(actor_state.direction);
    this->ammo = actor_state.ammo;
    this->actual_ammo = actor_state.actual_ammo;
    this->timeleft = actor_state.time_left;
    std::cout << "actual_ammo: " << this->actual_ammo << "\n";

    std::int32_t fixed_y_position =
            window_height - static_cast<std::int32_t>(
                    static_cast<float>(actor_state.position_y) *
                    static_cast<float>(window_height) * ROAD_RATIO / SV_MAP_HEIGHT);

    sprite_destination.SetY(fixed_y_position);

    std::int32_t actor_x_pos = actor_state.position_x;
    std::int32_t relative_x_pos_to_window = actor_x_pos - window_x_pos;
    sprite_destination.SetX(relative_x_pos_to_window);

    if (relative_x_pos_to_window < -TOLERANCE || relative_x_pos_to_window > window_width + TOLERANCE) {
        drawable = false;
    } else {
        drawable = true;
    }
    hp_drawer.updateInfo(static_cast<float>(actor_state.actual_health) / static_cast<float>(actor_state.health), sprite_destination);

}

void ActorDrawer::draw(std::uint32_t frame_ticks) {

    std::uint8_t last_sprite = sprite_index;

    if (!drawable)
        return;

    animation_manager.draw(type, animation, &sprite_index, direction,
                           sprite_destination, frame_ticks - previous_frame_ticks);


    if (last_sprite != sprite_index)
        previous_frame_ticks = frame_ticks;
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

void ActorDrawer::drawBar() {
    hp_drawer.draw();
}
