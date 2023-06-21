//
// Created by luan on 20/06/23.
//

#ifndef TP_PICK_SOLDIER_SCOUT_H
#define TP_PICK_SOLDIER_SCOUT_H
#include "../information.h"

class PickScoutSoldierRequest : public Information {

public:
    PickScoutSoldierRequest() = default;

    [[nodiscard]] std::vector<int8_t> serialize() const override;

    PickScoutSoldierRequest(const PickScoutSoldierRequest&) = delete;
    PickScoutSoldierRequest& operator=(const PickScoutSoldierRequest&) = delete;

    ~PickScoutSoldierRequest() override = default;
};
#endif //TP_PICK_SOLDIER_SCOUT_H
