//
// Created by luan on 20/06/23.
//

#ifndef TP_PICK_SOLDIER_P90_H
#define TP_PICK_SOLDIER_P90_H

#include "../information.h"

class PickP90SoldierRequest : public Information {

public:
    PickP90SoldierRequest() = default;

    [[nodiscard]] std::vector<int8_t> serialize() const override;

    PickP90SoldierRequest(const PickP90SoldierRequest&) = delete;
    PickP90SoldierRequest& operator=(const PickP90SoldierRequest&) = delete;

    ~PickP90SoldierRequest() override = default;
};

#endif //TP_PICK_SOLDIER_P90_H
