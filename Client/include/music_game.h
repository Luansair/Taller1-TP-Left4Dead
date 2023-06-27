//
// Created by luan on 27/06/23.
//

#ifndef TP_MUSIC_GAME_H
#define TP_MUSIC_GAME_H

#include <SDL2pp/Music.hh>
#include <SDL2pp/Mixer.hh>

class GameMusic {
    SDL2pp::Mixer mixer;
    SDL2pp::Music music;

public:
    GameMusic();

    void startMusic();
    void pauseMusic();
    void changeMusicStatus();
};

#endif //TP_MUSIC_GAME_H
