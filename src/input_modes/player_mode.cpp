#include <AceButton.h>
#include "../classes/InputHandler.h"
#include "../common/mp3.h"
#include "../common/debug.h"
#include "../common/global.h"
#include "player_mode.h"

using namespace mp3;
using namespace ace_button;


namespace player_mode {
    bool isPlaying = false;
    uint8_t currentFolder;
    uint8_t currentTrack;

    InputHandler* handler;
    void handleRed(AceButton *, uint8_t eventType, uint8_t) {
        switch (eventType) {
            case AceButton::kEventPressed:
                if (isPlaying) player.start();
                else player.pause();
                isPlaying = !isPlaying;
        }
    }

    void handleBlue(AceButton *, uint8_t eventType, uint8_t) {
        switch (eventType) {
            case AceButton::kEventPressed:
                DEBUG_PRINT(F("Increasing volume"));
                player.increaseVolume();
        }
    }

    void handleYellow(AceButton *, uint8_t eventType, uint8_t) {
        switch (eventType) {
            case AceButton::kEventPressed:
                DEBUG_PRINT(F("Next track"));
                player.nextTrack();
        }
    }

    void handleWhite(AceButton*, uint8_t eventType, uint8_t) {
        switch (eventType) {
            case AceButton::kEventPressed:
                DEBUG_PRINT(F("Previous track"));
                player.prevTrack();
        }
    }

    void handleGreen(AceButton *, uint8_t eventType, uint8_t) {
        switch (eventType) {
            case AceButton::kEventPressed:
                DEBUG_PRINT(F("Decreasing volume"));
                player.decreaseVolume();
        }
    }

    void play(uint8_t folder, uint8_t track) {
        currentTrack = track;
        currentFolder = folder;
        player.playFolderTrack(folder, track);
    }

    void nextTrack() {
        currentTrack++;
        play(currentFolder, currentTrack);
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
        global::playlist = true;
        handler->loop();
    }
}

