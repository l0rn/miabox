#include <SPI.h>
#include <MFRC522.h>
#include "mp3.h"
#include "nfc.h"
#include "input_mode.h"
#include "../assets/Assets.h"
#include "./debug.h"
#include "utils.h"

namespace nfc {
    MFRC522::MIFARE_Key blankClassicKey = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
    MFRC522::MIFARE_Key blankUltralightKey = { 0xFF, 0xFF, 0xFF, 0xFF };
    uint8_t blankUltralightACK[] = { 0, 0 };

    bool readerIsBlocked = false;

    MFRC522 reader(NFC_SLAVE_SELECT_PIN, NFC_RESET_PIN);
    void setup() {
        SPI.begin();
        reader.PCD_Init();
    }


    void closeTagConnection() {
        readerIsBlocked = false;
        reader.PICC_HaltA();
        reader.PCD_StopCrypto1();
    }

    bool readNfcTag(NfcTag* tag) {
        uint8_t nfcTagReadBuffer[NFC_READ_BUFFER_SIZE];
        bool success = readNfcTagData(nfcTagReadBuffer);
        if (!success) {
            return false;
        }
        // check if identifier matches
        uint64_t tagIdentifier = utils::uint8ArrayToUint64(nfcTagReadBuffer, 0);
        tag->newCard = tagIdentifier != USED_TAG_IDENTIFIER;
        tag->type = nfcTagReadBuffer[TAG_TYPE_INDEX];
        tag->folderNumber = nfcTagReadBuffer[TAG_FOLDER_INDEX];
        return true;
    }

    bool readNfcTagData(uint8_t* nfcTagReadBuffer) {
        MFRC522::PICC_Type piccType = reader.PICC_GetType(reader.uid.sak);
        bool success;
        if (piccType == MFRC522::PICC_TYPE_MIFARE_MINI ||
            piccType ==  MFRC522::PICC_TYPE_MIFARE_1K ||
            piccType == MFRC522::PICC_TYPE_MIFARE_4K
        ) {
            DEBUG_PRINT(F("Card is a mifare classic"));
            success = readMifareClassic(nfcTagReadBuffer);
            if (!success) {
                return false;
            }
        } else if (piccType == MFRC522::PICC_TYPE_MIFARE_UL) {
            DEBUG_PRINT(F("Card is a mifare UL"));
            success = readMifareUL(nfcTagReadBuffer);
            if (!success) {
                return false;
            }
        } else {
            DEBUG_PRINT(F("Card is unsupported"));
            closeTagConnection();
            return false;
        }
        return true;
    }

    MFRC522::StatusCode authenticateMifareClassic() {
        return (MFRC522::StatusCode)reader.PCD_Authenticate(
                MFRC522::PICC_CMD_MF_AUTH_KEY_A,
                MIFARE_CLASSIC_TRAILER_BLOCK,
                &blankClassicKey,
                &reader.uid);
    }

    MFRC522::StatusCode authenticateMifareUL() {
        return (MFRC522::StatusCode)reader.PCD_NTAG216_AUTH(blankUltralightKey.keyByte, blankUltralightACK);
    }

    bool authenticateTag() {
        MFRC522::PICC_Type piccType = reader.PICC_GetType(reader.uid.sak);
        MFRC522::StatusCode piccStatus;
        if (piccType == MFRC522::PICC_TYPE_MIFARE_MINI ||
            piccType ==  MFRC522::PICC_TYPE_MIFARE_1K ||
            piccType == MFRC522::PICC_TYPE_MIFARE_4K
                ) {
            DEBUG_PRINT(F("Authenticating a mifare classic"));
            piccStatus = authenticateMifareClassic();
        } else if (piccType == MFRC522::PICC_TYPE_MIFARE_UL) {
            DEBUG_PRINT(F("Authenticating a mifare UL"));
            piccStatus = authenticateMifareUL();
        } else {
            DEBUG_PRINT(F("Card is unsupported"));
            closeTagConnection();
            return false;
        }
        if (piccStatus == MFRC522::STATUS_OK) { return true; }
        else {
            DEBUG_PRINT("Card authentication failed: "); DEBUG_PRINT(MFRC522::GetStatusCodeName(piccStatus));
        }
    }

    bool readMifareClassic(uint8_t* nfcTagReadBuffer) {
        MFRC522::StatusCode piccStatus;
        uint8_t piccReadBuffer[NFC_READ_BUFFER_SIZE];
        uint8_t piccBufferSize = sizeof(piccReadBuffer);
        uint8_t classicBlock = 4;
        DEBUG_PRINT(F("Card authenticated"));
        // read 16 bytes from nfc tag (by default sector 1 / block 4)
        piccStatus = (MFRC522::StatusCode)reader.MIFARE_Read(classicBlock, piccReadBuffer, &piccBufferSize);
        if (piccStatus == MFRC522::STATUS_OK) {
            DEBUG_PRINT(F("Card read to buffer"));
            memcpy(nfcTagReadBuffer, piccReadBuffer, NFC_READ_BUFFER_SIZE);
            return true;
        } else {
            DEBUG_PRINT("MIFARE_read failed with status: "); DEBUG_PRINT((uint8_t)piccStatus); Serial.print("\n");
            return false;
        }
    }

    bool readMifareUL(uint8_t* nfcTagReadBuffer) {
        uint8_t piccReadBuffer[NFC_READ_BUFFER_SIZE];
        uint8_t piccBufferSize = sizeof(piccReadBuffer);
        bool success = false;
        MFRC522::StatusCode piccStatus;
        uint8_t ultralightStartPage = 8;

        // read 16 bytes from nfc tag (by default pages 8-11)
        for (uint8_t ultralightPage = ultralightStartPage; ultralightPage < ultralightStartPage + 4; ultralightPage++) {
            piccStatus = (MFRC522::StatusCode)reader.MIFARE_Read(ultralightPage, piccReadBuffer, &piccBufferSize);
            if (piccStatus == MFRC522::STATUS_OK) {
                success = true;
                memcpy(nfcTagReadBuffer + ((ultralightPage * 4) - (ultralightStartPage * 4)), piccReadBuffer, 4);
            }
            else {
                success = false;
                DEBUG_PRINT("Reading Mifare UL failed with: ");DEBUG_PRINT(reader.GetStatusCodeName(piccStatus));
                break;
            }
        }
        return success;
    }

    bool writeMifareClassic(uint8_t* nfcTagWriteBuffer) {
        uint8_t piccWriteBuffer[NFC_WRITE_BUFFER_SIZE];
        MFRC522::StatusCode piccStatus;
        uint8_t classicBlock = 4;
        memset(piccWriteBuffer, 0, NFC_WRITE_BUFFER_SIZE);
        memcpy(piccWriteBuffer, nfcTagWriteBuffer, NFC_WRITE_BUFFER_SIZE);
        piccStatus = (MFRC522::StatusCode)reader.MIFARE_Write(classicBlock, piccWriteBuffer, NFC_WRITE_BUFFER_SIZE);
        if (piccStatus == MFRC522::STATUS_OK) {
           return true;
        } else {
            DEBUG_PRINT("Card write failed with status: "); DEBUG_PRINT(reader.GetStatusCodeName(piccStatus));
            return false;
        }
    }

    bool writeMifareUL(uint8_t* nfcTagWriteBuffer) {
        uint8_t piccWriteBuffer[NFC_WRITE_BUFFER_SIZE];
        bool success = false;
        MFRC522::StatusCode piccStatus;
        uint8_t ultralightStartPage = 8;

        for (uint8_t ultralightPage = ultralightStartPage; ultralightPage < ultralightStartPage + 4; ultralightPage++) {
            memset(piccWriteBuffer, 0, sizeof(piccWriteBuffer));
            memcpy(piccWriteBuffer, nfcTagWriteBuffer + ((ultralightPage * 4) - (ultralightStartPage * 4)), 4);
            piccStatus = (MFRC522::StatusCode)reader.MIFARE_Write(ultralightPage, piccWriteBuffer, sizeof(piccWriteBuffer));
            if (piccStatus == MFRC522::STATUS_OK) success = true;
            else {
                success = false;
                DEBUG_PRINT("Writing to mifare UL failed with: "); DEBUG_PRINT(reader.GetStatusCodeName(piccStatus));
                break;
            }
        }
        return success;
    }

    bool writeNfcTagObject(NfcTag* nfcTag) {
        uint8_t nfcTagBuffer[NFC_WRITE_BUFFER_SIZE];
        utils::uint64ToUint8Array(nfcTagBuffer, USED_TAG_IDENTIFIER, 0);
        nfcTagBuffer[TAG_TYPE_INDEX] = nfcTag->type;
        nfcTagBuffer[TAG_FOLDER_INDEX] = nfcTag->folderNumber;
        return writeNfcTagData(nfcTagBuffer);
    }

    bool writeNfcTagData(uint8_t* nfcTagWriteBuffer) {
        MFRC522::PICC_Type piccType = reader.PICC_GetType(reader.uid.sak);
        bool success = false;
        // decide which code path to take depending on picc type
        if (piccType == MFRC522::PICC_TYPE_MIFARE_MINI || piccType ==  MFRC522::PICC_TYPE_MIFARE_1K || piccType == MFRC522::PICC_TYPE_MIFARE_4K) {
            success = writeMifareClassic(nfcTagWriteBuffer);
        } else if (piccType == MFRC522::PICC_TYPE_MIFARE_UL) {
            success = writeMifareUL(nfcTagWriteBuffer);
        } else {
            DEBUG_PRINT(F("Unsupported card Type"));
        }
        return success;
    }

    bool eraseNfcTagData() {
        uint8_t nullBuffer[NFC_WRITE_BUFFER_SIZE];
        for (uint8_t i = 0; i < NFC_WRITE_BUFFER_SIZE; i++) {
            nullBuffer[i] = 0;
        }
        return writeNfcTagData(nullBuffer);
    }
}