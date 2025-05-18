#ifndef __DATA_H__
#define __DATA_H__

#include <Arduino.h>

struct ObdData {
    uint16_t coolant;
    uint16_t voltage;
    uint16_t rpm;
    uint16_t distance;
    float maf_rate;
};

enum ObdStatus {
    BT_INIT_FAILED = 0,
    BT_INIT_SUCCESS,
    BT_CONNECTING,
    BT_CONNECT_FAILED,
    OBD_INIT_FAILED,
    OBD_INIT_SUCCESS,
    OBD_CONNECTED,
    OBD_DISCONNECTED
};

extern String ObdString[8];

#endif