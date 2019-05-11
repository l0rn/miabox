#include <AceButton.h>
#include "InputHandler.h"
#include <DFMiniMp3.h>


using namespace ace_button;

/*
 * Initializes an InputHandler with a function for each button
 * @
 */
InputHandler::InputHandler(
        ButtonConfig::EventHandler redHandler,
        ButtonConfig::EventHandler blueHandler,
        ButtonConfig::EventHandler yellowHandler,
        ButtonConfig::EventHandler greenHandler
) {
    redConfig.setEventHandler(redHandler);
    blueConfig.setEventHandler(blueHandler);
    yellowConfig.setEventHandler(yellowHandler);
    greenConfig.setEventHandler(greenHandler);
    redButton = new AceButton(&redConfig);
    blueButton = new AceButton(&blueConfig);
    greenButton = new AceButton(&greenConfig);
    yellowButton = new AceButton(&yellowConfig);
    redButton->init(RED_PIN);
    blueButton->init(BLUE_PIN);
    yellowButton->init(YELLOW_PIN);
    greenButton->init(GREEN_PIN);
}

void InputHandler::setupPinModes() {
    pinMode(RED_PIN, INPUT_PULLUP);
    pinMode(BLUE_PIN, INPUT_PULLUP);
    pinMode(YELLOW_PIN, INPUT_PULLUP);
    pinMode(GREEN_PIN, INPUT_PULLUP);
}

void InputHandler::loop() {
    redButton->check();
    blueButton->check();
    yellowButton->check();
    greenButton->check();
}

void noopHandler(AceButton*, uint8_t, uint8_t) {}