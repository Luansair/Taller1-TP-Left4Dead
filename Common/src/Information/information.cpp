#include "../../include/Information/information.h"

// This function may be deleted in the future.
// The reason is that the socket.recv already do this with any type of data.
std::uint32_t
Information::deserializeFourBytesNumber(const std::vector<int8_t>&
        serialized_number) {
    using std::uint32_t;

    uint32_t bigendian_game_code = 0;
    for (int i = 1; i < 5; i++) {
        uint32_t mask = 0xFF;
        uint32_t byte = (static_cast<uint32_t>(serialized_number[i]) & mask) <<
                (8 * (i - 1));
        bigendian_game_code |= byte;
    }
    return ntohl(bigendian_game_code);
}

std::uint8_t Information::get_type(void) const {
    // le pongo asi para no tener que hacer la funcion en todos los que heredan y no necesito
    return VOID;
}