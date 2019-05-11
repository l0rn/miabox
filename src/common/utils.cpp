#include <Arduino.h>
#include "utils.h"

namespace utils {
    uint64_t uint8ArrayToUint64(const uint8_t* array, uint8_t low) {
        return ((uint64_t) array[low + 7] << 56u) |
               ((uint64_t) array[low + 6] << 48u) |
               ((uint64_t) array[low + 5] << 40u) |
               ((uint64_t) array[low + 4] << 32u) |
               ((uint64_t) array[low + 3] << 24u) |
               ((uint64_t) array[low + 2] << 16u) |
               ((uint64_t) array[low + 1] << 8u) |
               ((uint64_t) array[low] << 0u);
    }

    void uint64ToUint8Array(uint8_t* array, uint64_t value, uint8_t low) {
        array[low] = (value & 0x00000000000000FFu) >> 0u;
        array[low + 1] = (value & 0x000000000000FF00u) >> 8u;
        array[low + 2] = (value & 0x0000000000FF0000u) >> 16u;
        array[low + 3] = (value & 0x00000000FF000000u) >> 24u;
        array[low + 4] = (value & 0x000000FF00000000u) >> 32u;
        array[low + 5] = (value & 0x0000FF0000000000u) >> 40u;
        array[low + 6] = (value & 0x00FF000000000000u) >> 48u;
        array[low + 7] = (value & 0xFF00000000000000u) >> 56u;
    }
}