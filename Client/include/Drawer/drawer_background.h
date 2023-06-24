//
// Created by luan on 22/06/23.
//

#ifndef TP_DRAWER_BACKGROUND_H
#define TP_DRAWER_BACKGROUND_H

#include "../Background/background_manager.h"
#include "drawer_layer.h"

// Puedo tener varios background drawers en drawer manager.
class BackgroundDrawer {
    BackgroundManager background_manager;
    std::uint8_t background_type;
    std::array<LayerDrawer, WAR_1_BEHIND_COUNT> layers_to_draw_behind; // care with the order.
    std::array<LayerDrawer, WAR_1_FRONT_COUNT> layers_to_draw_ahead;

public:
    explicit BackgroundDrawer(SDL2pp::Renderer& renderer,
                     std::uint8_t background_type,
                     std::int32_t window_width, std::int32_t window_height);

    void updateInfo(std::int32_t window_x_pos, std::int32_t window_width, std::int32_t window_height);

    void drawBehindLayers();
};
#endif //TP_DRAWER_BACKGROUND_H
