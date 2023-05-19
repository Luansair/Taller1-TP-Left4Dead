#include <exception>
#include <SDL2pp/SDL2pp.hh>
#include "yaml-cpp/yaml.h"
#include "../include/client.h"

Client::Client(const char *hostname, const char *servname) {
}

void Client::init() {
    using SDL2pp::SDL;
    using SDL2pp::Window;
    using SDL2pp::Renderer;
    using SDL2pp::Texture;

    using YAML::Node;
    using YAML::LoadFile;

    SDL sdl(SDL_INIT_VIDEO);

    Node window_config = LoadFile(CLIENT_CONFIG_PATH "/config.yaml")["window"];

    const auto window_width = window_config["width"].as<std::uint16_t>();
    const auto window_height = window_config["height"].as<std::uint16_t>();

    Window window("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, SDL_WINDOW_RESIZABLE);

    Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

    Texture sprites(renderer, RESOURCES_PATH "/Spear/Walk.png");

    renderer.Clear();

    renderer.Copy(sprites);

    renderer.Present();

    SDL_Delay(5000);

}