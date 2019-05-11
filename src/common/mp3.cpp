#include <Arduino.h>
#include <SoftwareSerial.h>
#include <DFMiniMp3.h>
#include "mp3.h"
#include "../input_modes/player_mode.h"
#include "global.h"

namespace mp3 {
    SoftwareSerial mp3Serial(MP3_SERIAL_RX, MP3_SERIAL_TX);
    Mp3Player player(mp3Serial);

    void Mp3Notify::OnError(uint16_t returnValue) {
        switch (returnValue) {
            case DfMp3_Error_Busy:
                Serial.print(F("busy"));
                break;
            case DfMp3_Error_Sleeping:
                Serial.print(F("sleep"));
                break;
            case DfMp3_Error_SerialWrongStack:
                Serial.print(F("serial stack"));
                break;
            case DfMp3_Error_CheckSumNotMatch:
                Serial.print(F("checksum"));
                break;
            case DfMp3_Error_FileIndexOut:
                Serial.print(F("file index"));
                break;
            case DfMp3_Error_FileMismatch:
                Serial.print(F("file mismatch"));
                break;
            case DfMp3_Error_Advertise:
                Serial.print(F("advertise"));
                break;
            case DfMp3_Error_General:
                Serial.print(F("general"));
                break;
            default:
                Serial.print(F("unknown"));
                break;
        }
        Serial.print(F(" error "));
        Serial.println(returnValue);
    }

    void Mp3Notify::OnPlayFinished(uint16_t returnValue) {
        Serial.print(F("Finished playing track: ")); Serial.println(returnValue);
        if (global::playlist) { player_mode::nextTrack(); }
    }

    void Mp3Notify::OnCardOnline(uint16_t returnValue) {
        Serial.print(F("sd online "));
        Serial.println(returnValue);
    }

    void Mp3Notify::OnCardInserted(uint16_t returnValue) {
        Serial.print(F("sd in "));
        Serial.println(returnValue);
    }

    void Mp3Notify::OnCardRemoved(uint16_t returnValue) {
        Serial.print(F("sd out "));
        Serial.println(returnValue);
    }

    void Mp3Notify::OnUsbOnline(uint16_t returnValue) {
        Serial.print(F("usb online "));
        Serial.println(returnValue);
    }

    void Mp3Notify::OnUsbInserted(uint16_t returnValue) {
        Serial.print(F("usb in "));
        Serial.println(returnValue);
    }

    void Mp3Notify::OnUsbRemoved(uint16_t returnValue) {
        Serial.print(F("usb out "));
        Serial.println(returnValue);
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