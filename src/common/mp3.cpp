#include <Arduino.h>
#include <SoftwareSerial.h>
#include <DFMiniMp3.h>
#include "mp3.h"
#include "../input_modes/player_mode.h"
#include "./debug.h"
#include "global.h"

namespace mp3 {
    SoftwareSerial mp3Serial(MP3_SERIAL_RX, MP3_SERIAL_TX);
    Mp3Player player(mp3Serial);

    void Mp3Notify::OnError(uint16_t returnValue) {
        switch (returnValue) {
            case DfMp3_Error_Busy:
                DEBUG_PRINT(F("busy"));
                break;
            case DfMp3_Error_Sleeping:
                DEBUG_PRINT(F("sleep"));
                break;
            case DfMp3_Error_SerialWrongStack:
                DEBUG_PRINT(F("serial stack"));
                break;
            case DfMp3_Error_CheckSumNotMatch:
                DEBUG_PRINT(F("checksum"));
                break;
            case DfMp3_Error_FileIndexOut:
                DEBUG_PRINT(F("file index"));
                break;
            case DfMp3_Error_FileMismatch:
                DEBUG_PRINT(F("file mismatch"));
                break;
            case DfMp3_Error_Advertise:
                DEBUG_PRINT(F("advertise"));
                break;
            case DfMp3_Error_General:
                DEBUG_PRINT(F("general"));
                break;
            default:
                DEBUG_PRINT(F("unknown"));
                break;
        }
        DEBUG_PRINT(F(" error "));
        DEBUG_PRINT(returnValue);
    }

    void Mp3Notify::OnPlayFinished(uint16_t returnValue) {
        DEBUG_PRINT(F("Finished playing track: ")); DEBUG_PRINT(returnValue);
        if (global::playlist) { player_mode::nextTrack(); }
    }

    void Mp3Notify::OnCardOnline(uint16_t returnValue) {
        DEBUG_PRINT(F("sd online "));
        DEBUG_PRINT(returnValue);
    }

    void Mp3Notify::OnCardInserted(uint16_t returnValue) {
        DEBUG_PRINT(F("sd in "));
        DEBUG_PRINT(returnValue);
    }

    void Mp3Notify::OnCardRemoved(uint16_t returnValue) {
        DEBUG_PRINT(F("sd out "));
        DEBUG_PRINT(returnValue);
    }

    void Mp3Notify::OnUsbOnline(uint16_t returnValue) {
        DEBUG_PRINT(F("usb online "));
        DEBUG_PRINT(returnValue);
    }

    void Mp3Notify::OnUsbInserted(uint16_t returnValue) {
        DEBUG_PRINT(F("usb in "));
        DEBUG_PRINT(returnValue);
    }

    void Mp3Notify::OnUsbRemoved(uint16_t returnValue) {
        DEBUG_PRINT(F("usb out "));
        DEBUG_PRINT(returnValue);
    }

    void setup() {
        player.begin();
        player.setVolume(DEFAULT_VOLUME);
    }

    bool busy() {
        return digitalRead(MP3_BUSY_PIN) == 0;
    }

    void loop() {
        player.loop();
    }

    void playMessage(uint16_t messageId, bool blocking) {
        uint16_t waited = 0;
        player.playMp3FolderTrack(messageId);
        // player has a stupid delay
        delay(100);
        // wait until the player actually starts
        while (!busy() && waited < MAX_WAIT_FOR_BUSY) {
            loop();
            delay(10);
            waited+=10;
        }
        // if blocking stop computation until message is done
        while (blocking && busy()) { delay(10); }
    }

    void playMessageNonBlocking(uint16_t messageId) {
        playMessage(messageId, false);
    }

    void playMessageBlocking(uint16_t messageId) {
        playMessage(messageId, true);
    }
}