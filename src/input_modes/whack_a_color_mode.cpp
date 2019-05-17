#include <AceButton.h>
#include "whack_a_color_mode.h"
#include "../classes/InputHandler.h"
#include "../assets/Assets.h"
#include "../assets/CustomAssets.h"
#include "../common/mp3.h"
#include "../common/input_mode.h"
#include "../common/debug.h"

using namespace ace_button;

namespace whack_a_color_mode {
    uint8_t buttonPins[] = { BLUE_PIN, WHITE_PIN, RED_PIN, YELLOW_PIN, GREEN_PIN };
    uint16_t messageMap[5][2] = {
            { BLUE_PIN, SIMON_BLUE},
            { WHITE_PIN, SIMON_WHITE},
            { RED_PIN, SIMON_RED},
            { YELLOW_PIN, SIMON_YELLOW},
            { GREEN_PIN, SIMON_GREEN},
    };
    uint8_t expectedColor;
    InputHandler* handler;


    void input(uint8_t buttonPin) {
        if (buttonPin == expectedColor) {
                mp3::playMessageBlocking(JONNI_CORRECT);
        } else {
            mp3::playMessageBlocking(JONNI_FALSE);
        }
        nextColor();
    }

    uint16_t getMessage(uint8_t pin) {
        for (uint8_t i = 0; i < sizeof(messageMap); i++) {
            if (messageMap[i][0] == pin) return messageMap[i][1];
        }
        return 0;
    }

    void handle(AceButton* button, uint8_t eventType, uint8_t) {
        DEBUG_PRINT_LN("handle:begin");
        switch (eventType) {
            case AceButton::kEventPressed:
                DEBUG_PRINT("Pressed: "); DEBUG_PRINT_LN(button->getPin());
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

    void nextColor() {
        const uint8_t nextColor = buttonPins[random(0,5)];
        mp3::playMessageNonBlocking(getMessage(nextColor));
        expectedColor = nextColor;
        DEBUG_PRINT_LN("nextColor:finished");
    }

    void loop() {
        DEBUG_PRINT_LN("loop:begin");
        handler->loop();
        DEBUG_PRINT_LN("loop:finished");
    }

    void startGame() {
        mp3::playMessageBlocking(WHACK_A_COLOR);
        input_mode::change(loop);
        nextColor();
    }
}