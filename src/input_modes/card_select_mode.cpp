#include <AceButton.h>
#include "../assets/Assets.h"
#include "../classes/InputHandler.h"
#include "../common/input_mode.h"
#include "../common/mp3.h"
#include "../common/nfc.h"
#include "card_select_mode.h"

InputHandler *handler;
uint8_t browseFolder = 1;

namespace card_select_mode {
    void handleRed(AceButton *, uint8_t eventType, uint8_t) {
        switch (eventType) {
            case AceButton::kEventPressed:
                writeMusicTag();
        }
    }

    void handleBlue(AceButton *, uint8_t eventType, uint8_t) {
        switch (eventType) {
            case AceButton::kEventPressed:
                browseFolder++;
                mp3::player.playFolderTrack(browseFolder, 1);
        }
    }

    void handleYellow(AceButton *, uint8_t eventType, uint8_t) {
    }

    void handleGreen(AceButton *, uint8_t eventType, uint8_t) {
        switch (eventType) {
            case AceButton::kEventPressed:
                if (browseFolder <= 1) return;
                else browseFolder--;
                mp3::player.playFolderTrack(browseFolder, 1);
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

    void writeMusicTag() {
        nfc::NfcTag newTag = {
                .newCard = false,
                .type = MUSIC_TAG,
                .folderNumber = browseFolder
        };
        bool success = nfc::writeNfcTagObject(&newTag);
        if (success) {
            mp3::playMessageBlocking(CARD_WRITE_SUCCESS);
        } else {
            Serial.println(F("Card write error"));
            mp3::playMessageBlocking(CARD_WRITE_ERROR);
        }
        nfc::closeTagConnection();
    }

    void newCard() {
        browseFolder = 1;
        input_mode::change(loop);
    }

    void loop() {
        handler->loop();
    }
}