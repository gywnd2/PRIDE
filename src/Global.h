#ifndef __GLOBAL__
#define __GLOBAL__

#include <Arduino.h>
#include <BluetoothSerial.h>
#include <lvgl.h>
#include <Data.h>
#include <MP3.h>
#include <OBD.h>
#include <TripMgr.h>
#include <Widget.h>
#include <Display.h>
#include <Storage.h>
#include <WelcomeMgr.h>

/*
CS (Chip Select): GPIO 5
MOSI (Master Out Slave In): GPIO 23
CLK (Clock): GPIO 18
MISO (Master In Slave Out): GPIO 19
*/

#define OBD_SIMUL_MODE
#define OBD_SIMUL_QUERY_TIME 5000
#define SERIAL_BAUDRATE 115200
#define WELCOME_TRACK_NUM 1
#define GOODBYE_TRACK_NUM 2
#define LOG_INTERVAL 3000
#define OBD_QUERY_INVALID_RESPONSE 9999
#define BT_CONNECTION_CHECK_INTERVAL 1000

class Mp3Mgr;
class OBDMgr;
class StorageMgr;
class TripMgr;
class WidgetMgr;
class DisplayMgr;
class WelcomeMgr;

extern StorageMgr storage;
extern WidgetMgr widget;
extern WelcomeMgr welcome;
extern DisplayMgr display;
extern Mp3Mgr dfp;
extern OBDMgr obd;
extern TripMgr trip;
extern BluetoothSerial serial_bt;
extern bool isLvglInit;
extern bool isWidgetUpdateNeeded;

extern char cpu_usage[6];
extern char ram_usage[6];

#endif