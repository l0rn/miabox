cmake_minimum_required(VERSION 3.8.2)

project(Miabox)

arduino_cmake_project(Miabox BOARD_NAME nano BOARD_CPU atmega328old)

add_arduino_executable(Miabox
        miabox.cpp
        src/common/global.cpp
        src/common/mp3.cpp
        src/common/nfc.cpp
        src/common/input_mode.cpp
        src/common/nfc_mode.cpp
        src/common/utils.cpp
        src/common/mode_switcher.cpp
        src/input_modes/drumset_mode.cpp
        src/input_modes/card_select_mode.cpp
        src/input_modes/player_mode.cpp
        src/input_modes/simon_says_mode.cpp
        src/input_modes/whack_a_color_mode.cpp
        src/nfc_modes/card_erase_mode.cpp
        src/nfc_modes/card_read_mode.cpp
        src/classes/InputHandler.cpp
)


# libraries
find_arduino_library(aceButton AceButton ${board_id} 3RD_PARTY)
link_arduino_library(Miabox aceButton ${board_id})

find_arduino_library(dfPlayer DFPlayer_Mini_Mp3_by_Makuna ${board_id} 3RD_PARTY HEADER_ONLY)
link_arduino_library(Miabox dfPlayer ${board_id} HEADER_ONLY)

find_arduino_library(softwareSerial SoftwareSerial ${board_id} 3RD_PARTY)
link_arduino_library(Miabox softwareSerial ${board_id})

find_arduino_library(rfid MFRC522 ${board_id} 3RD_PARTY)
link_arduino_library(Miabox rfid ${board_id})

set_target_upload_port(Miabox /dev/ttyUSB0)