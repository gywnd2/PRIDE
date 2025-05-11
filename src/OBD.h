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
        bool obd_busy = false;
        BluetoothSerial *bt;
        ELM327 myELM327;
        ObdData obd_data;
        int obd_status = BT_INIT_FAILED;
        const String obd_name = "OBDII";
        uint8_t obd_addr[6]={0x01, 0x23, 0x45, 0x67, 0x89, 0xba};

        void QueryCoolant(uint16_t &coolant_temp);
        void QueryVoltage(uint16_t &voltage_level);
        void QueryRPM(uint16_t &rpm_value);
        void QueryDistAfterEcuBoot(uint16_t &distance);

        TaskHandle_t query_obd_data_task = NULL;
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
        static void ConnectBTTask(void *param);
        bool IsOBDInitialized(void);
        ObdData GetObdData(void);
        void SetCoolantTemp(uint16_t val);
        void SetVoltageLevel(uint16_t val);
        void SetRPM(uint16_t val);
        void SetDistance(uint16_t val);
        void SetOBDStatus(int status);
        int GetOBDStatus(void);

        static void QueryOBDData(void *param);
};

#endif