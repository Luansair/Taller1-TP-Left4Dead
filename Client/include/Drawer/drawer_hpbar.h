//
// Created by luan on 26/06/23.
//

#ifndef TP_DRAWER_HPBAR_H
#define TP_DRAWER_HPBAR_H

#include <SDL2pp/Renderer.hh>

class HealthBarDrawer {
    SDL2pp::Renderer& renderer;
    SDL2pp::Color actual_hp_color;
    SDL2pp::Color empty_hp_color;
    SDL2pp::Rect actual_hp_bar;
    SDL2pp::Rect empty_hp_bar;

public:
    explicit HealthBarDrawer(SDL2pp::Renderer& renderer);

    void updateInfo(float hp_percent, const SDL2pp::Point &actor_sprite_dest);

    void draw();
};
#endif //TP_DRAWER_HPBAR_H
