#include <Arduino.h>

struct ObdData {
    uint16_t coolant;
    uint16_t voltage;
    uint16_t rpm;
};