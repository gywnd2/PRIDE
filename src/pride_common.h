#ifndef __PRIDE_COMMON__
#define __PRIDE_COMMON__

#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "ui.h"
#include <BluetoothSerial.h>
#include <Global.h>

void NotifyPlaySound(int track_num);
bool NotifyConnectOBD(uint8_t remoteAddress[]);
void UpdateOBDStatus(int status);
void UpdateVoltage(char *val);
void UpdateCoolant(char *val);
void UpdateCpuUsage(char &val);
void UpdateRamUsage(char &val);
BluetoothSerial& RequestBTSerial(void);

#endif