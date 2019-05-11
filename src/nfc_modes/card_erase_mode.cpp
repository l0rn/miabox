//
// Created by jonni on 11.05.19.
//

#include "card_erase_mode.h"
#include "../common/nfc.h"
#include "../common/mp3.h"
#include "../common/input_mode.h"
#include "../common/nfc_mode.h"
#include "../nfc_modes/card_read_mode.h"
#include "../input_modes/player_mode.h"
#include "../assets/Assets.h"

using namespace nfc;

namespace card_erase_mode {
    void loop() {
        bool success = nfc::eraseNfcTagData();
        if (success) {
            mp3::playMessageBlocking(CARD_DELETE_SUCCESS);
        } else {
            mp3::playMessageBlocking(CARD_WRITE_ERROR);
        }
        closeTagConnection();
        nfc_mode::change(card_read_mode::loop);
    }
}