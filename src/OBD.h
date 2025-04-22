#ifndef __OBD__
#define __OBD__

#include <pride_common.h>
#include <ELMduino.h>

#define RPM_REQ_RETRY_MAX 2

struct ObdData {
    uint16_t coolant;
    uint16_t voltage;
    uint16_t rpm;
};

class OBDMgr
{
    private:
        ELM327 myELM327;
        String obd_name = "OBDII";
        uint8_t obd_addr[6]={0x01, 0x23, 0x45, 0x67, 0x89, 0xba};
        ObdData obd_data;
        void QueryCoolant(uint16_t &coolant_temp);
        void QueryVoltage(uint16_t &voltage_level);
    public:
        OBDMgr()
        {
            Serial.println("====OBDMgr");
        }
        ~OBDMgr()
        {
            Serial.println("~~~~OBDMgr");
        }
        
        bool InitOBD(void);
        void InitBTTask(void *param);
        bool ConnectOBD(BluetoothSerial &bt_serial);
        void UpdateOBDData(uint16_t &coolant_temp, uint16_t &voltage_level, uint16_t &rpm_value);
        void QueryRPM(uint16_t &rpm_value);
        ObdData* GetObdData(void);
        void SetCoolantTemp(uint16_t val);
        void SetVoltageLevel(uint16_t val);
        void SetRPM(uint16_t val);
        
        static void Query30SecData(uint16_t &voltage_level, uint16_t &coolant_temp);
};

#endif