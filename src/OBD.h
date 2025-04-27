#ifndef __OBD__
#define __OBD__

#include <Arduino.h>
#include <pride_common.h>
#include <ELMduino.h>
#include <BluetoothSerial.h>
#include <Data.h>
#include "esp_task_wdt.h"

#define RPM_REQ_RETRY_MAX 2

class OBDMgr
{
    private:
        bool obd_init = false;
        BluetoothSerial *bt;
        ELM327 myELM327;
        ObdData obd_data;
        const String obd_name = "OBDII";
        uint8_t obd_addr[6]={0x01, 0x23, 0x45, 0x67, 0x89, 0xba};

        void QueryCoolant(uint16_t &coolant_temp);
        void QueryVoltage(uint16_t &voltage_level);
        
        TaskHandle_t query_coolant_voltage_handler = NULL;
        TaskHandle_t query_rpm = NULL;
    public:
        OBDMgr()
        {
            Serial.println("====OBDMgr");
        }
        ~OBDMgr()
        {
            Serial.println("~~~~OBDMgr");
        }
        
        void InitOBD(void);
        bool IsOBDInitialized(void);
        void InitBTTask(void *param);
        ObdData GetObdData(void);
        void SetCoolantTemp(uint16_t val);
        void SetVoltageLevel(uint16_t val);
        void SetRPM(uint16_t val);
        
        static void QueryRPM(void *param);
        static void Query30SecData(void *param);
};

#endif