#include <cstdint>
#include <vector>

#ifndef TP_ACTION_H
#define TP_ACTION_H

#include <netinet/in.h>
#include <stdexcept>

class Information {

protected:
    Information() = default;

    template <typename T>
    void serializeNumber(std::vector<int8_t>& result, T number) const {
        using std::uint32_t;
        using std::uint8_t;
        using std::size_t;

        size_t number_type_size = sizeof(number);
        T big_endian_number;

        if (number_type_size == sizeof(uint32_t)) {
            big_endian_number = htonl(number);
        } else if (number_type_size == sizeof(uint16_t)) {
            big_endian_number = htons(number);
        } else {
            throw std::runtime_error("Information::serializeNumber. Invalid "
                                     "Number type");
        }

        for (size_t index = 0; index < number_type_size; index++) {
            // The mask guarantee that the 8 less significant bits are extracted.
            T mask = 0xFF;
            size_t amount_bits_to_shift = index * 8;
            uint32_t shifted_number = big_endian_number >> amount_bits_to_shift;
            uint32_t filtered_number = shifted_number & mask;
            auto byte = static_cast<int8_t>(filtered_number);
            result.push_back(byte);
        }
    }

    static std::uint32_t deserializeFourBytesNumber(const std::vector<int8_t>&
            serialized_number);
public:

    [[nodiscard]] virtual std::vector<int8_t> serialize() const
    = 0;

    Information(Information&&) = default;
    Information& operator=(Information&&) = delete;

    Information(const Information&) = default;
    Information& operator=(const Information&) = delete;

    virtual ~Information() = default;
};

#endif //TP_ACTION_H
