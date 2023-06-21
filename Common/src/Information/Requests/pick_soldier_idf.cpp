//
// Created by luan on 20/06/23.
//
#include "../../../include/Information/Requests/pick_soldier_idf.h"


std::vector<int8_t> PickIdfSoldierRequest::serialize() const {
    return {REQUEST_PICK_IDF_SOLDIER};
}