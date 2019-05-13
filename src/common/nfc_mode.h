
#ifndef MIABOX_NFC_MODE_H
#define MIABOX_NFC_MODE_H


namespace nfc_mode {
    typedef struct nfc_mode {
        void (*loop)();
    };
    extern nfc_mode current;
    void change(void (*loop)());
    void loop();
}

#endif //MIABOX_NFC_MODE_H
