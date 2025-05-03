#include <Global.h>
#include <MP3.h>
#include <OBD.h>

// Global variable definitions
Mp3Mgr dfp;
OBDMgr obd;
BluetoothSerial serial_bt;
bool isLvglInit = false;
bool iswidgetUpdateNeeded = false;

char cpu_usage[6] = {0};
char ram_usage[6] = {0};