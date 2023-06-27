//
// Created by luan on 22/06/23.
//
#include "../../include/Drawer/drawer_background.h"
// Puedo dividir los layers en repetible y no repetible (cielo, sol y calle deben repetirse, el resto no por ser deco)
BackgroundDrawer::BackgroundDrawer(SDL2pp::Renderer& renderer, std::uint8_t background_type,
                                   std::int32_t window_width, std::int32_t window_height) :
    background_manager(renderer),
    background_type(background_type),
    layers_to_draw_behind{
            LayerDrawer(background_manager, WAR_1_LAYER_SKY, 0, window_width, window_width),
            LayerDrawer(background_manager, WAR_1_LAYER_SUN, 0, window_width, window_width),
            LayerDrawer(background_manager, WAR_1_LAYER_RUINS, 0.2, window_width, window_width),
            LayerDrawer(background_manager, WAR_1_LAYER_HOUSE_3, 0.4, window_width, window_width),
            LayerDrawer(background_manager, WAR_1_LAYER_HOUSE_2, 0.6, window_width, window_width),
            LayerDrawer(background_manager, WAR_1_LAYER_HOUSE_1, 0.8, window_width, window_width),
            LayerDrawer(background_manager, WAR_1_LAYER_ROAD, 1, window_width, window_width),
    },
    layers_to_draw_ahead{
            LayerDrawer(background_manager, WAR_1_LAYER_FENCE, 0, window_width, window_width)
    } {

}

void BackgroundDrawer::drawBehindLayers() {

    for (auto& layer : layers_to_draw_behind) {
        layer.draw(background_type);
    }
}

void BackgroundDrawer::updateInfo(std::int32_t window_x_pos, std::int32_t window_width, std::int32_t window_height) {
    for (auto& layer : layers_to_draw_behind) {
        layer.updateInfo(window_x_pos, window_width, window_height);
    }
}

