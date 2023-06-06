#ifndef TP_DRAWER_ANIMATION_H
#define TP_DRAWER_ANIMATION_H

#include <SDL2pp/SDL2pp.hh>
#include "draw_info_dto.h"

// Cargar al inicio del juego y pasarlo crear texture manager y pasasr texture
// Texture y sprites pueden ser referencias dado que solo se leen.
// De esta manera no se hace una texture y sprites para cada objeto (q son
// cosas de lectura!)
// TextureManager->SoldierOneTexture->draw(index,flip,dest)
// Esto dado que tiene lo base pero nada de info del destino y la misma cambia
// con el tiempo (eso no puede ser una referencia constante!)
class AnimationDrawer {
    SDL2pp::Renderer& renderer;
    SDL2pp::Texture texture;
    std::vector<SDL2pp::Rect> sprites;
    std::uint8_t sprite_index;
    std::uint8_t sprite_flip;
    SDL2pp::Rect sprite_destination;

public:
    AnimationDrawer(SDL2pp::Renderer& renderer, const std::string &sprite_filepath);
    void nextSprite();
    void reset();
    void prevSprite();
    void updateInfo(const DrawInfoDTO& draw_info);
    void draw(unsigned int frame_ticks);
};

#endif // TP_DRAWER_ANIMATION_H
