#ifndef __PRIDE_COMMON__
#define __PRIDE_COMMON__

#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "MP3.h"
#include "Storage.h"
#include "Display.h"
#include "OBD.h"
#include "Widget.h"
#include "WelcomeMgr.h"

bool NotifyOBDConnect(void);
void UpdateGauge(void);
void UpdateOBDStatus(char *status);
void UpdateVoltage(char *val);
void UpdateCoolant(char *val);

#endif