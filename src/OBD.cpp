
#include <OBD.h>

bool OBDMgr::InitOBD(void)
{
    
}

bool OBDMgr::ConnectOBD(BluetoothSerial &bt_serial)
{    
    bool bt_connected = bt_serial.connect(obd_addr);
    if(bt_connected)
    {
        if(myELM327.begin(bt_serial, true, 2000))
        {
            return true;
        }
        else
        { 
            UpdateOBDStatus("OBD Service Failed");
        }
    }
    else
    {
        UpdateOBDStatus("BT Connect Failed");
    }

    return false;
}

void OBDMgr::UpdateOBDData(uint16_t &coolant_temp, uint16_t &voltage_level, uint16_t &rpm_value)
{
    // 30sec task
    QueryCoolant(coolant_temp);
    QueryVoltage(voltage_level);

    // 3sec task
    QueryRPM(rpm_value);
    
    if(myELM327.nb_rx_state == ELM_SUCCESS) UpdateOBDStatus("OBD Connected");
    else if(myELM327.nb_rx_state == ELM_NO_DATA) UpdateOBDStatus("Good bye!");
    else UpdateOBDStatus("OBD Disconnected");
}

void OBDMgr::QueryCoolant(uint16_t &coolant_temp)
{
    while(true)
    {
        float coolant = myELM327.engineCoolantTemp();
        if(myELM327.nb_rx_state == ELM_SUCCESS)
        {
            coolant_temp = (uint16_t)coolant;
            Serial.println("coolant level set to "+(String)coolant_temp);
            break;
        }
        else if(myELM327.nb_rx_state == ELM_NO_DATA)
        {
            coolant_temp = 9999;
            break;
        }
        delay(10);
    }
}

void OBDMgr::QueryVoltage(uint16_t &voltage_level)
{
    while(true)
    {
        float voltage = myELM327.batteryVoltage();
        if(myELM327.nb_rx_state == ELM_SUCCESS)
        {
            voltage_level = (uint16_t)voltage;
            Serial.println("voltage level set to "+(String)voltage_level);
            break;
        }
        else if(myELM327.nb_rx_state == ELM_NO_DATA)
        {
            voltage_level = 9999;
            break;
        }
        delay(10);
    }
}

void OBDMgr::Query30SecData(uint16_t &voltage_level, uint16_t &coolant_temp)
{
    QueryVoltage(voltage_level);
    QueryCoolant(coolant_temp);
}

void OBDMgr::QueryRPM(uint16_t &rpm_value)
{
    int rpm_retry_count = 0;
    while(true)
    {
        float rpm = myELM327.rpm();
        if(myELM327.nb_rx_state == ELM_SUCCESS)
        {
            rpm_retry_count = 0;
            rpm_value = (uint16_t)rpm;
            break;
        }
        else if(myELM327.nb_rx_state == ELM_NO_DATA)
        {
            if(rpm_retry_count == 2)
            {
                rpm_value = 9999;
                break;
            }
            else
            {
                rpm_retry_count++;
            }
        }

        delay(10);
    }
}

ObdData* OBDMgr::GetObdData(void)
{
    return &obd_data;
}

void OBDMgr::SetCoolantTemp(uint16_t val)
{
    obd_data.coolant = val;
}

void OBDMgr::SetVoltageLevel(uint16_t val)
{
    obd_data.voltage = val;
}

void OBDMgr::SetRPM(uint16_t val)
{
    obd_data.rpm = val;
}