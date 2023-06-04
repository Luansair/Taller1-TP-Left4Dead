//
// Created by luan on 04/06/23.
//

#ifndef TP_SERIALIZER_H
#define TP_SERIALIZER_H

#include <cstdint>
#include <vector>

class Serializer {
public:
    static void serializeFourBytesNumber(std::vector<int8_t>& result,
                                         std::uint32_t number);

    static std::uint32_t deserializeFourBytesNumber(const std::vector<int8_t>&
    serialized_number);
};
#endif //TP_SERIALIZER_H
