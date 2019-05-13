#ifndef MIABOX_DRUMSET_MODE_H
#define MIABOX_DRUMSET_MODE_H

#define DRUMS_FOLDER 99
#define KICK_SOUND DRUMS_FOLDER, 1
#define SNARE_SOUND DRUMS_FOLDER, 2
#define HIHAT_SOUND DRUMS_FOLDER, 3
#define TOM_SOUND DRUMS_FOLDER, 4
#define CLAP_SOUND DRUMS_FOLDER, 5

namespace drumset_mode {
    void setup();
    void loop();
}


#endif //MIABOX_DRUMSET_MODE_H
