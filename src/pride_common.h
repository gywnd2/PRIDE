#ifndef __PRIDE_COMMON__
#define __PRIDE_COMMON__

#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "ui.h"
#include <MP3.h>
#include <OBD.h>
#include <BluetoothSerial.h>

void NotifyPlaySound(int track_num);
void UpdateOBDStatus(char *status);
void UpdateVoltage(char *val);
void UpdateCoolant(char *val);

#endif