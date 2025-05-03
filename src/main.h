#ifndef __PRIDE_MAIN__
#define __PRIDE_MAIN__

#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include <MP3.h>
#include <Storage.h>
#include <Widget.h>
#include <WelcomeMgr.h>
#include <Display.h>
#include <Global.h>

StorageMgr storage;
WidgetMgr widget;
WelcomeMgr welcome;
DisplayMgr display;
TaskHandle_t *bt_task_handler = NULL;
TaskHandle_t *cal_cpu_ram_handler = NULL;
TaskHandle_t *welcome_handler = NULL;

#endif