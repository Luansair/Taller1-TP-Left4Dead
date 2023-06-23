//
// Created by luan on 23/06/23.
//
#include "../../include/Drawer/drawer_layer.h"

LayerDrawer::LayerDrawer(BackgroundManager &background_manager, std::uint8_t layer_type, double speed,
                         std::int32_t window_width, std::int32_t window_height) :
        background_manager(background_manager),
        layer_type(layer_type),
        speed(speed),
        x1(-window_width), x2(0), x3(window_width),
        previous_layer_x(&x1), middle_layer_x(&x2), next_layer_x(&x3),
        width(window_width), height(window_height),
        last_windows_x_pos(0) {
}

void LayerDrawer::draw(std::uint8_t background_type) {
    SDL2pp::Rect layer_1 = {x1, 0, width, height};
    SDL2pp::Rect layer_2 = {x2, 0, width, height};
    SDL2pp::Rect layer_3 = {x3, 0, width, height};

    background_manager.drawLayer(background_type, layer_type, layer_1);
    background_manager.drawLayer(background_type, layer_type, layer_2);
    background_manager.drawLayer(background_type, layer_type, layer_3);
}

void LayerDrawer::updateInfo(std::int32_t window_x_pos, std::int32_t window_width, std::int32_t window_height) {
    width = window_width;
    height = window_height;
    std::int32_t traveled_distance = window_x_pos - last_windows_x_pos;
    if (traveled_distance > window_width) {
        last_windows_x_pos = window_x_pos;
        return;
    }
    x1 = x1 - static_cast<std::int32_t>(traveled_distance * speed);
    x2 = x2 - static_cast<std::int32_t>(traveled_distance * speed);
    x3 = x3 - static_cast<std::int32_t>(traveled_distance * speed);

    if (x1 < - window_width * 1.5 ) {
        x1 = x3 + window_width;
    } else if (x1 > window_width * 1.5) {
        x1 = x2 - window_width;

    } else if (x2 < - window_width * 1.5) {
        x2 = x1 + window_width;

    } else if (x2 > window_width * 1.5) {
        x2 = x3 - window_width;

    } else if (x3 < - window_width * 1.5) {
        x3 = x2 + window_width;

    } else if (x3 > window_width * 1.5) {
        x3 = x1 - window_width;

    }
    last_windows_x_pos = window_x_pos;
    /*
    while (*next_layer_x < window_x_pos + window_width ||
            *previous_layer_x > window_x_pos - window_width) {
        x1 = x1 - static_cast<std::int32_t>(window_x_pos * speed);
        x2 = x2 - static_cast<std::int32_t>(window_x_pos * speed);;
        x3 = x3 - static_cast<std::int32_t>(window_x_pos * speed);

        if (x1 < window_x_pos - window_width * 1.5 && x1 != *next_layer_x) {
            x1 = x3 + window_width;
            next_layer_x = &x1;
        } else if (x1 >= window_x_pos + window_width * 1.5) {
            x1 = x2 - window_width;
            previous_layer_x = &x1;
        } else if (x2 < - window_width * 1.5) {
            x2 = x1 + window_width;
            next_layer_x = &x2;
        } else if (x2 >= window_width * 1.5) {
            x2 = x3 - window_width;
            previous_layer_x = &x2;
        } else if (x3 < window_width * 1.5) {
            x3 = x2 + window_width;
            next_layer_x = &x3;
        } else if (x3 >= window_width * 1.5) {
            x3 = x1 - window_width;
            previous_layer_x = &x3;
        }
    }
     */
}

