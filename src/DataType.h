#ifndef __DATA_TYPE__
#define __DATA_TYPE__

#include <Arduino.h>

#define WELCOME_TRACK_NUM 1
#define GOODBYE_TRACK_NUM 2

struct ObdData {
    uint16_t coolant;
    uint16_t voltage;
    uint16_t rpm;
};

#endif