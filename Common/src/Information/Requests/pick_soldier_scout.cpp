//
// Created by luan on 20/06/23.
//
#include "../../../include/Information/Requests/pick_soldier_scout.h"


std::vector<int8_t> PickScoutSoldierRequest::serialize() const {
    return {REQUEST_PICK_SCOUT_SOLDIER};
}