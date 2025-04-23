#ifndef __PRIDE_MAIN__
#define __PRIDE_MAIN__

#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include <MP3.h>
#include <Storage.h>
#include <Widget.h>
#include <OBD.h>
#include <WelcomeMgr.h>
#include <Display.h>
#include <BluetoothSerial.h>

Mp3Mgr dfp;
StorageMgr storage;
WidgetMgr widget;
OBDMgr obd;
WelcomeMgr welcome;
BluetoothSerial serial_bt;
DisplayMgr display;
TaskHandle_t *bt_task_handler = NULL;
TaskHandle_t *cal_cpu_ram_handler = NULL;
TaskHandle_t *welcome_handler = NULL;

void UpdateGauge(OBDMgr &obd);

#endif