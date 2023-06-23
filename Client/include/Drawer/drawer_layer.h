//
// Created by luan on 23/06/23.
//

#ifndef TP_DRAWER_LAYER_H
#define TP_DRAWER_LAYER_H

#include <cstdint>
#include "../Background/background_manager.h"

class LayerDrawer {
    BackgroundManager& background_manager;
    const std::uint8_t layer_type;

    double speed;

    std::int32_t x1;
    std::int32_t x2;
    std::int32_t x3;

    std::int32_t* previous_layer_x;
    std::int32_t* middle_layer_x;
    std::int32_t* next_layer_x;

    std::int32_t width;
    std::int32_t height;

    std::int32_t last_windows_x_pos;

public:
    LayerDrawer(BackgroundManager& background_manager, std::uint8_t layer_type, double speed,
               std::int32_t window_width, std::int32_t window_height);

    void draw(std::uint8_t background_type);

    void updateInfo(std::int32_t window_x_pos, std::int32_t window_width, std::int32_t window_height);

    LayerDrawer(LayerDrawer&&) = default;
    LayerDrawer& operator=(LayerDrawer&&) = delete;

    LayerDrawer(const LayerDrawer&) = delete;
    LayerDrawer& operator=(const LayerDrawer&) = delete;

    ~LayerDrawer() = default;
};


#endif //TP_DRAWER_LAYER_H
