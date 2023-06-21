//
// Created by luan on 20/06/23.
//
#include "../../../include/Information/Requests/pick_soldier_p90.h"


std::vector<int8_t> PickP90SoldierRequest::serialize() const {
    return {REQUEST_PICK_P90_SOLDIER};
}
