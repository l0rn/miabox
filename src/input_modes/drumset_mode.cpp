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
                player.playFolderTrack(KICK_SOUND);
        }
    }

    void handleBlue(AceButton *, uint8_t eventType, uint8_t) {
        switch (eventType) {
            case AceButton::kEventPressed:
                player.playFolderTrack(SNARE_SOUND);
        }
    }

    void handleYellow(AceButton *, uint8_t eventType, uint8_t) {
        switch (eventType) {
            case AceButton::kEventPressed:
                player.playFolderTrack(HIHAT_SOUND);
        }
    }

    void handleGreen(AceButton *, uint8_t eventType, uint8_t) {
        switch (eventType) {
            case AceButton::kEventPressed:
                player.playFolderTrack(TOM_SOUND);
        }
    }

    void handleWhite(AceButton *, uint8_t eventType, uint8_t) {
        switch (eventType) {
            case AceButton::kEventPressed:
                player.playFolderTrack(CLAP_SOUND);
        }
    }

    void setup() {
        handler = new InputHandler(
            handleRed,
            handleBlue,
            handleYellow,
            handleGreen,
            handleWhite
        );
    }

    void loop() {
        handler->loop();
    }
}

