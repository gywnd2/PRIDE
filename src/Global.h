#ifndef __DATA_TYPE__
#define __DATA_TYPE__

#include <Arduino.h>
#include <MP3.h>
#include <OBD.h>
#include <Storage.h>
#include <BluetoothSerial.h>

#define WELCOME_TRACK_NUM 1
#define GOODBYE_TRACK_NUM 2

class Mp3Mgr;
class OBDMgr;
class StorageMgr;

extern Mp3Mgr dfp;
extern OBDMgr obd;
extern StorageMgr storage;
extern BluetoothSerial serial_bt;

#endif