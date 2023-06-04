#include <cstdint>
#include <vector>

#ifndef TP_ACTION_H
#define TP_ACTION_H

class Action {

protected:
    Action() = default;

    static void serializeFourBytesNumber(std::vector<int8_t>& result,
                                         std::uint32_t number);

    static std::uint32_t deserializeFourBytesNumber(const std::vector<int8_t>&
            serialized_number);
public:

    [[nodiscard]] virtual std::vector<int8_t> serialize() const
    = 0;

    Action(Action&&) = default;
    Action& operator=(Action&&) = delete;

    Action(Action&) = default;
    Action& operator=(Action&) = delete;

    virtual ~Action() = default;
};

#endif //TP_ACTION_H
