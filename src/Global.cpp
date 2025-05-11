#include <Global.h>

// Global variable definitions
Mp3Mgr dfp;
OBDMgr obd;
TripMgr trip;
WidgetMgr widget;
DisplayMgr display;
StorageMgr storage;
WelcomeMgr welcome;

BluetoothSerial serial_bt;
bool isLvglInit = false;
bool iswidgetUpdateNeeded = false;

char cpu_usage[6] = {0};
char ram_usage[6] = {0};