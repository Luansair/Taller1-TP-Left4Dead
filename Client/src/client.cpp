#include <exception>
#include <SDL2pp/SDL2pp.hh>
#include "yaml-cpp/yaml.h"
#include "../include/client.h"

Client::Client(const char *hostname, const char *servname) {
}

void Client::init() {
    SDL2pp::SDL sdl(SDL_INIT_VIDEO);
    YAML::Emitter out;
    out << "Hello world";
    std::cout << "YAML out: " << out.c_str() << std::endl;
}