#include "nfc_mode.h"
#include "./nfc.h"
#include "./mp3.h"
#include "./debug.h"
#include "../nfc_modes/card_read_mode.h"
#include "../assets/Assets.h"

using namespace nfc;

namespace nfc_mode {
    nfc_mode current = {
        // default mode is card read
        .loop = card_read_mode::loop
    };

    void change(void (*loop)()) {
        current.loop = loop;
    }

    void loop() {
        if (readerIsBlocked) return;
        if (reader.PICC_IsNewCardPresent() && reader.PICC_ReadCardSerial()) {
            DEBUG_PRINT(F("Card detected"));
            bool success = authenticateTag();
            if (!success) {
                DEBUG_PRINT("Card authentication error");
                closeTagConnection();
                mp3::playMessageBlocking(CARD_WRITE_ERROR);
                return;
            }
            current.loop();
        }
    }
}