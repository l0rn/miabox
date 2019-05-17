
#ifndef MIABOX_SIMON_SAYS_MODE_H
#define MIABOX_SIMON_SAYS_MODE_H

#include <AceButton.h>

#define SIMON_SAYS_MAX 30

using namespace ace_button;

namespace simon_says_mode {
    void setup();
    void startGame();
    void loop();
    void nextRound();
}


#endif //MIABOX_SIMON_SAYS_MODE_H
