//
// Created by luan on 26/06/23.
//
#include "../../include/Drawer/drawer_hpbar.h"

HealthBarDrawer::HealthBarDrawer(SDL2pp::Renderer &renderer) :
    renderer(renderer),
    actual_hp_color(50,255,50,255),
    empty_hp_color(0,0,0,255),
    actual_hp_bar(0,0,64,10),
    empty_hp_bar(0,0,64,10) {

}

void HealthBarDrawer::updateInfo(float hp_percent, const SDL2pp::Point &actor_sprite_dest) {
    auto actual_width = static_cast<std::int32_t>(static_cast<float>(empty_hp_bar.GetW()) * hp_percent);
    actual_hp_bar.SetW(actual_width);
    std::int32_t bars_pos_x = actor_sprite_dest.GetX() + 32 - 64;
    std::int32_t bars_pos_y = actor_sprite_dest.GetY() + 43 - 64;

    actual_hp_bar.SetX(bars_pos_x);
    empty_hp_bar.SetX(bars_pos_x);

    actual_hp_bar.SetY(bars_pos_y);
    empty_hp_bar.SetY(bars_pos_y);
}

void HealthBarDrawer::draw() {
    renderer.SetDrawColor(empty_hp_color);
    renderer.FillRect(empty_hp_bar);

    renderer.SetDrawColor(actual_hp_color);
    renderer.FillRect(actual_hp_bar);

}

