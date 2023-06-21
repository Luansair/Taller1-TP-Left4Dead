//
// Created by luan on 20/06/23.
//

#ifndef TP_PICK_SOLDIER_IDF_H
#define TP_PICK_SOLDIER_IDF_H
#include "../information.h"

class PickIdfSoldierRequest : public Information {

public:
    PickIdfSoldierRequest() = default;

    [[nodiscard]] std::vector<int8_t> serialize() const override;

    PickIdfSoldierRequest(const PickIdfSoldierRequest&) = delete;
    PickIdfSoldierRequest& operator=(const PickIdfSoldierRequest&) = delete;

    ~PickIdfSoldierRequest() override = default;
};
#endif //TP_PICK_SOLDIER_IDF_H
