#include <AceButton.h>
#include "simon_says_mode.h"
#include "../classes/InputHandler.h"
#include "../assets/Assets.h"
#include "../common/mp3.h"
#include "../common/input_mode.h"

using namespace ace_button;

namespace simon_says_mode {
    uint8_t buttonPins[] = { BLUE_PIN, WHITE_PIN, RED_PIN, YELLOW_PIN, GREEN_PIN };
    uint16_t messageMap[5][2] = {
        { BLUE_PIN, SIMON_BLUE},
        { WHITE_PIN, SIMON_WHITE},
        { RED_PIN, SIMON_RED},
        { YELLOW_PIN, SIMON_YELLOW},
        { GREEN_PIN, SIMON_GREEN},
    };
    uint8_t simonSays[SIMON_SAYS_MAX];
    uint16_t userPointer = 0;
    uint16_t round = 0;
    InputHandler* handler;
    bool inputLocked = true;


    void input(uint8_t buttonPin) {
        Serial.print("User pointer is: "); Serial.println(userPointer);
        Serial.print("Expected simon value is: "); Serial.println(simonSays[userPointer]);
        Serial.print("Input is: "); Serial.println(buttonPin);
        if (buttonPin == simonSays[userPointer]) {
            if (userPointer == (round - 1)) {
                mp3::playMessageBlocking(SIMON_CORRECT);
                nextRound();
            } else {
                userPointer++;
            }
        } else {
            mp3::playMessageBlocking(SIMON_LOST);
            startGame();
        }
    }

    uint16_t getMessage(uint8_t pin) {
        for (uint8_t i = 0; i < sizeof(messageMap); i++) {
            if (messageMap[i][0] == pin) return messageMap[i][1];
        }
        return 0;
    }

    void handle(AceButton* button, uint8_t eventType, uint8_t) {
        switch (eventType) {
            case AceButton::kEventPressed:
                Serial.print("Pressed: "); Serial.println(button->getPin());
                input(button->getPin());
        }
    }

    void setup() {
        handler = new InputHandler(
            handle,
            handle,
            handle,
            handle,
            handle
        );
    }

    void nextRound() {
        inputLocked = true;
        userPointer = 0;
        simonSays[round] = buttonPins[random(0,4)];
        for (uint16_t i = 0; i <= round; i++) {
            mp3::playMessageBlocking(getMessage(simonSays[i]));
        }
        round++;
        inputLocked = false;
    }

    void loop() {
        if (!inputLocked) {
            handler->loop();
        }
    }

    void startGame() {
        mp3::playMessageBlocking(SIMON_SAYS_START);
        // reset round
        round = 0;
        input_mode::change(loop);
        nextRound();
    }
}