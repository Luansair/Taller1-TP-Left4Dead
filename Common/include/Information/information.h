#include <cstdint>
#include <vector>

#ifndef TP_ACTION_H
#define TP_ACTION_H

class Information {

protected:
    Information() = default;

    static void serializeFourBytesNumber(std::vector<int8_t>& result,
                                         std::uint32_t number);

    static std::uint32_t deserializeFourBytesNumber(const std::vector<int8_t>&
            serialized_number);
public:

    [[nodiscard]] virtual std::vector<int8_t> serialize() const
    = 0;

    Information(Information&&) = default;
    Information& operator=(Information&&) = delete;

    Information(Information&) = default;
    Information& operator=(Information&) = delete;

    virtual ~Information() = default;
};

#endif //TP_ACTION_H
