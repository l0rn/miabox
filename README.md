# Miabox

This project is my attempt for a software solution for the marvellous [TonUINO](https://www.voss.earth/tonuino/) project.
As I was a bit disappointed by the limited features of the official arduino IDE and the poor maintainability of the code, 
which resides all in one file, I decided to develop my own software instead of the ["official one"](https://github.com/xfjx/TonUINO).
The hardware I used are exactly the parts like described in the original instructions.

**This code was heavily inspired by:**

* https://github.com/seisfeld/TonUINO
* https://github.com/xfjx/TonUINO

But completely rewritten after all.

## Building

This is a cmake project, making use of the great work of [Arduino-CMake-NG](https://github.com/arduino-cmake/Arduino-CMake-NG).
It integrates perfectly with [CLion](https://www.jetbrains.com/clion/) IDE.

## Helper scripts

In the `scripts/` folder you will find some important scripts.

### Generate introduction messages

You can have Google read the album names and prepend it before playing. The command below will search for subfolders
in the folder in the first argument, create an introduction, and copies over the albums in the appropriate format for the DFPlayer.
**Be aware that the former sd card contents will be completely deleted.**

```
./scripts/prepare_music_folders.py ~/Music/for-my-tonuino /path/to/sdcard -k MYGOOGLEKEYWITHTEXTTOSPEECHPERMISSION
``` 

### Generate status messages

To operate the device it is required to have voice feedback. Execute the script below to generate and copy the required status messages.

```
./scripts/voice_assets_to_sdcard.py assets/audio_messages_de.txt /path/to/sdcard -k MYGOOGLEKEYWITHTEXTTOSPEECHPERMISSION
```

### Generate asset headers

If you are not planning to change / add messages in `assets/audio_messages_de.txt` you won't need this.
To have easy access to the status messages in your code you can generate C++ headers for status messages like so:

```
./scripts/generate_asset_headers.py assets/audio_messages_de.txt
```

It will update `src/assets/Assets.h` accordingly.

## Code

The code aims to be verbose in naming and somewhat self-documenting, comments generally are in form of `Serial.print` statements.
After all it is a hobbyist project, while maintaining some patterns of well organized code I might have taken some shortcuts for the sake of development speed.

## Questions / Contribute?

If you like my attempt for TonUINO, have issues or like to contribute feel free to open an issue or a PR.


Cheers, and thanks again to Mr.Voß and the great Idea of TonUINO