#include <netinet/in.h>
#include "../../include/Information/information.h"

void Information::serializeFourBytesNumber(std::vector<int8_t>& result,
                                           std::uint32_t number) {
    using std::uint32_t;
    using std::uint8_t;

    uint32_t big_endian_number = htonl(number);
    for (int i = 0; i < 4; i++) {
        // The mask guarantee that the 8 less significant bits are extracted.
        uint32_t mask = 0xFF;  // 00000000000000000000000011111111
        auto byte = static_cast<int8_t>((big_endian_number >> (i * 8)) & mask);
        result.push_back(byte);
    }
}

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
