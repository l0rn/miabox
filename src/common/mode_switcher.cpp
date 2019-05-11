#include "mode_switcher.h"
#include "../nfc_modes/card_erase_mode.h"
#include "../classes/InputHandler.h"
#include "../common/mp3.h"
#include "../assets/Assets.h"
#include "nfc_mode.h"

namespace mode_switcher {
    InputHandler* handler;

    void setup() {
        handler = new InputHandler();
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

    void loop () {
        cardEraseMode();
    }
}