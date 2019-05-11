#include "input_mode.h"
#include "global.h"

namespace input_mode {
    struct input_mode {
        void (*loop)();
    } current;

    void change(void (*loop)()) {
        global::playlist = false;
        current.loop = loop;
    }

    void loop() {
        current.loop();
    }
}