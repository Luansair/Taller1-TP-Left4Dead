//
// Created by luan on 27/06/23.
//
#include "../../include/music_game.h"

GameMusic::GameMusic() :
        mixer(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096),
        music(RESOURCES_PATH "/music/zerg_theme_3.mp3") {

}

void GameMusic::startMusic() {
    mixer.PlayMusic(music);
}

void GameMusic::pauseMusic() {
    mixer.PauseMusic();
}

void GameMusic::changeMusicStatus() {
    if (!mixer.IsMusicPlaying()) {
        startMusic();
    } else {
        if (mixer.IsMusicPaused()) {
            mixer.ResumeMusic();
        } else {
            pauseMusic();
        }
    }
}

