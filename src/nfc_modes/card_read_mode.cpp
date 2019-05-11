#include "../common/nfc.h"
#include "../common/mp3.h"
#include "../common/input_mode.h"
#include "../input_modes/card_select_mode.h"
#include "../input_modes/player_mode.h"
#include "../assets/Assets.h"
#include "card_read_mode.h"

using namespace nfc;

namespace card_read_mode {
    void loop() {
        NfcTag tag;
        bool success;
        success = readNfcTag(&tag);
        if (!success) {
            closeTagConnection();
            mp3::playMessageBlocking(CARD_READ_ERROR);
            return;
        }
        if (tag.newCard) {
            mp3::playMessageNonBlocking(NEW_CARD);
            Serial.println("Setting up new card");
            readerIsBlocked = true;
            card_select_mode::newCard();
        } else {
            player_mode::play(tag.folderNumber, 1);
            input_mode::change(player_mode::loop);
            closeTagConnection();
        }
    }
}