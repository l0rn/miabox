#include "Arduino.h"
#include <AceButton.h>
#ifndef MIABOX_INPUTHANDLER_H
#define MIABOX_INPUTHANDLER_H

#define RED_PIN A0
#define GREEN_PIN A3
#define YELLOW_PIN A2
#define BLUE_PIN A1
#define WHITE_PIN A4

using namespace ace_button;

void noopHandler(AceButton*, uint8_t, uint8_t);

class InputHandler {
    ButtonConfig redConfig;
    ButtonConfig blueConfig;
    ButtonConfig yellowConfig;
    ButtonConfig greenConfig;
    ButtonConfig whiteConfig;
public:
    AceButton* redButton;
    AceButton* blueButton;
    AceButton* yellowButton;
    AceButton* greenButton;
    AceButton* whiteButton;
    InputHandler(
        ButtonConfig::EventHandler redHandler = noopHandler,
        ButtonConfig::EventHandler blueHandler = noopHandler,
        ButtonConfig::EventHandler yellowHandler = noopHandler,
        ButtonConfig::EventHandler greenHandler = noopHandler,
        ButtonConfig::EventHandler whiteHandler = noopHandler
    );
    void loop();
    static void setupPinModes();
};


#endif //MIABOX_INPUTHANDLER_H
