#include "Arduino.h"
#include <AceButton.h>
#ifndef MIABOX_INPUTHANDLER_H
#define MIABOX_INPUTHANDLER_H

#define RED_PIN A0
#define GREEN_PIN A1
#define YELLOW_PIN A2
#define BLUE_PIN A3

using namespace ace_button;

void noopHandler(AceButton*, uint8_t, uint8_t);

class InputHandler {
    ButtonConfig redConfig;
    ButtonConfig blueConfig;
    ButtonConfig yellowConfig;
    ButtonConfig greenConfig;
public:
    AceButton* redButton;
    AceButton* blueButton;
    AceButton* yellowButton;
    AceButton* greenButton;
    InputHandler(
        ButtonConfig::EventHandler redHandler = noopHandler,
        ButtonConfig::EventHandler blueHandler = noopHandler,
        ButtonConfig::EventHandler yellowHandler = noopHandler,
        ButtonConfig::EventHandler greenHandler = noopHandler
    );
    void loop();
    static void setupPinModes();
};


#endif //MIABOX_INPUTHANDLER_H
