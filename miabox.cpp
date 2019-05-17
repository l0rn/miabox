#include <Arduino.h>
#include "src/common/nfc.h"
#include "src/common/mp3.h"
#include "src/common/nfc_mode.h"
#include "src/common/input_mode.h"
#include "src/common/mode_switcher.h"
#include "src/common/debug.h"
#include "src/input_modes/drumset_mode.h"
#include "src/input_modes/card_select_mode.h"
#include "src/input_modes/simon_says_mode.h"
#include "src/input_modes/player_mode.h"
#include "src/input_modes/whack_a_color_mode.h"
#include "src/classes/InputHandler.h"
#include "src/assets/Assets.h"

void setup() {
    Serial.begin(9600);
    while (!Serial);
    DEBUG_PRINT_LN(F("Starting..."));
    DEBUG_PRINT_LN(F("Set up pins"));
    InputHandler::setupPinModes();

    DEBUG_PRINT_LN(F("Setting common modules..."));
    DEBUG_PRINT_LN(F("Set up mp3"));
    mp3::setup();
    DEBUG_PRINT_LN(F("Set up nfc"));
    nfc::setup();
    DEBUG_PRINT_LN(F("Set up mode switcher"));
    mode_switcher::setup();
    DEBUG_PRINT_LN(F("Setting up input_modes..."));
    DEBUG_PRINT_LN(F("Set up player mode"));
    player_mode::setup();
    DEBUG_PRINT_LN(F("Set up drumset mode"));
    drumset_mode::setup();
    DEBUG_PRINT_LN(F("Set up card select mode"));
    card_select_mode::setup();
    DEBUG_PRINT_LN(F("Set up simon says mode"));
    simon_says_mode::setup();
    DEBUG_PRINT_LN(F("Set up whack a color mode"));
    whack_a_color_mode::setup();

    DEBUG_PRINT_LN(F("Starting in player mode"));
    input_mode::change(player_mode::loop);

    DEBUG_PRINT_LN(F("Waiting a grace period for mp3 player to come online"));
    delay(2000);
    mp3::playMessageBlocking(WELCOME);
}

void loop() {
    // loops from common modules
    mp3::loop();
    mode_switcher::loop();

    // loops from current nfc and input mode
    nfc_mode::loop();
    input_mode::loop();
}

