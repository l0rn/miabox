#include "mode_switcher.h"
#include "../input_modes/drumset_mode.h"
#include "../input_modes/simon_says_mode.h"
#include "../nfc_modes/card_erase_mode.h"
#include "../nfc_modes/card_read_mode.h"
#include "../classes/InputHandler.h"
#include "../common/mp3.h"
#include "../assets/Assets.h"
#include "nfc_mode.h"
#include "input_mode.h"

namespace mode_switcher {
    InputHandler* handler;
    void setup() {
        handler = new InputHandler();
    }


    void escapeCardEraseMode() {
        if (
            nfc_mode::current.loop == card_erase_mode::loop &&
            (handler->blueButton->isPressedRaw() ||
            handler->redButton->isPressedRaw() ||
            handler->greenButton->isPressedRaw() ||
            handler->yellowButton->isPressedRaw() ||
            handler->whiteButton->isPressedRaw())
        ) {
            mp3::playMessageBlocking(CARD_WRITE_ABORT);
            nfc_mode::change(card_read_mode::loop);
        }
    }

    void cardEraseMode() {
        if (
                handler->blueButton->isPressedRaw() &&
                handler->redButton->isPressedRaw() &&
                handler->greenButton->isPressedRaw()
        ) {
            mp3::playMessageBlocking(CARD_DELETE_MODE);
            nfc_mode::change(card_erase_mode::loop);
        }
    }

    void simonSaysMode() {
        if (
                handler->greenButton->isPressedRaw() &&
                handler->redButton->isPressedRaw() &&
                handler->whiteButton->isPressedRaw()
        ) {
            simon_says_mode::startGame();
        }
    }

    void drumsetMode() {
        if (
                handler->blueButton->isPressedRaw() &&
                handler->redButton->isPressedRaw() &&
                handler->yellowButton->isPressedRaw()
        ) {
            mp3::playMessageBlocking(DRUMSET_MODE_START);
            input_mode::change(drumset_mode::loop);
        }
    }

    void loop () {
        simonSaysMode();
        cardEraseMode();
        escapeCardEraseMode();
        drumsetMode();
    }
}