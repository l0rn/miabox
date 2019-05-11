#ifndef MIABOX_NFC_H
#define MIABOX_NFC_H
#include <MFRC522.h>

#define NFC_SLAVE_SELECT_PIN 10
#define NFC_RESET_PIN 9

#define MIFARE_CLASSIC_TRAILER_BLOCK 7

#define NFC_READ_BUFFER_SIZE 24
#define NFC_WRITE_BUFFER_SIZE 16
#define MUSIC_TAG 1

#define USED_TAG_IDENTIFIER 3721656045381959683


#define TAG_TYPE_INDEX 9
#define TAG_FOLDER_INDEX 10

namespace nfc {
    extern MFRC522 reader;
    extern bool readerIsBlocked;
    typedef struct {
        bool newCard;
        uint8_t type;
        uint8_t folderNumber;
    } NfcTag;

    void setup();
    void loop();
    bool readNfcTag(NfcTag*);
    bool readMifareClassic(uint8_t*);
    bool readMifareUL(uint8_t*);
    bool readNfcTagData(uint8_t*);
    bool writeNfcTagData(uint8_t*);
    bool writeNfcTagObject(NfcTag*);
    bool authenticateTag();
    bool eraseNfcTagData();
    void closeTagConnection();

}

#endif //MIABOX_NFC_H
