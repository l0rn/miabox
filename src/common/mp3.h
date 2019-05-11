#include <SoftwareSerial.h>
#include <DFMiniMp3.h>

#ifndef MIABOX_MP3_H
#define MIABOX_MP3_H

#define MP3_SERIAL_TX 3
#define MP3_SERIAL_RX 2
#define MP3_BUSY_PIN 4

#define MAX_WAIT_FOR_BUSY 500

#define DEFAULT_VOLUME 5

namespace mp3 {
    class Mp3Notify {
    public:
        static void OnError(uint16_t returnValue);
        static void OnPlayFinished(uint16_t returnValue);
        static void OnCardOnline(uint16_t returnValue);
        static void OnCardInserted(uint16_t returnValue);
        static void OnCardRemoved(uint16_t returnValue);
        static void OnUsbOnline(uint16_t returnValue);
        static void OnUsbInserted(uint16_t returnValue);
        static void OnUsbRemoved(uint16_t returnValue);
    };
    typedef DFMiniMp3<SoftwareSerial, Mp3Notify> Mp3Player;
    extern SoftwareSerial mp3Serial;
    extern Mp3Player player;
    void setup();
    void loop();
    bool busy();
    void playMessageNonBlocking(uint16_t);
    void playMessageBlocking(uint16_t);
    void playMessage(uint16_t, bool);
}
#endif //MIABOX_MP3_H
