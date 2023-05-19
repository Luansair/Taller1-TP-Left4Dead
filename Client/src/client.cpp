#include <exception>
#include <SDL2pp/SDL2pp.hh>
#include "../include/client.h"

Client::Client(const char *hostname, const char *servname) {
}

void Client::init() {
    SDL2pp::SDL sdl(SDL_INIT_VIDEO);

}