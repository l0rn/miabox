#ifndef MIABOX_PLAYER_MODE_H
#define MIABOX_PLAYER_MODE_H
#include <Arduino.h>



namespace player_mode {
    void setup();
    void loop();
    void play(uint8_t, uint8_t);
    void nextTrack();
}


#endif //MIABOX_PLAYER_MODE_H
