#include <Arduino.h>
#include <AceButton.h>
#include "../classes/InputHandler.h"
#include "../common/mp3.h"
#include "drumset_mode.h"


using namespace mp3;
using namespace ace_button;


namespace drumset_mode {
    InputHandler* handler;
    void handleRed(AceButton *, uint8_t eventType, uint8_t) {
        switch (eventType) {
            case AceButton::kEventPressed:
                Serial.println("Play Kick");
                player.playFolderTrack(3, 1);
            case AceButton::kEventReleased:
                Serial.println("Red released");
        }
    }

    void handleBlue(AceButton *, uint8_t eventType, uint8_t) {
        switch (eventType) {
            case AceButton::kEventPressed:
                Serial.println("Play Snare");
                player.playFolderTrack(3, 2);
            case AceButton::kEventReleased:
                Serial.println("Blue released");
        }
    }

    void handleYellow(AceButton *, uint8_t eventType, uint8_t) {
        switch (eventType) {
            case AceButton::kEventPressed:
                Serial.println("Yellow pressed");
            case AceButton::kEventReleased:
                Serial.println("Yellow released");
        }
    }

    void handleGreen(AceButton *, uint8_t eventType, uint8_t) {
        switch (eventType) {
            case AceButton::kEventPressed:
                Serial.println("Play Hi-Hat");
                player.playFolderTrack(3, 3);
            case AceButton::kEventReleased:
                Serial.println("Green released");
        }
    }

    void setup() {
        handler = new InputHandler(
            handleRed,
            handleBlue,
            handleYellow,
            handleGreen
        );
    }

    void loop() {
        handler->loop();
    }
}

