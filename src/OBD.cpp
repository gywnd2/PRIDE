
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

void OBDMgr::Query30SecData(void *param)
{
    OBDMgr* self = static_cast<OBDMgr*>(param);
    ObdData* data = NULL;

    while(1)
    {
        data = self->GetObdData();
        self->QueryVoltage(data->voltage);
        self->QueryCoolant(data->coolant);
    
        vTaskDelay(30000 / portTICK_PERIOD_MS);
    }

}

void OBDMgr::QueryRPM(void *param)
{
    OBDMgr* self = static_cast<OBDMgr*>(param);
    ObdData* data = NULL;

    while(1)
    {
        int rpm_retry_count = 0;
        while(true)
        {
            data = self->GetObdData();

            float rpm = self->myELM327.rpm();
            if(self->myELM327.nb_rx_state == ELM_SUCCESS)
            {
                rpm_retry_count = 0;
                data->rpm = (uint16_t)rpm;
                break;
            }
            else if(self->myELM327.nb_rx_state == ELM_NO_DATA)
            {
                if(rpm_retry_count == 2)
                {
                    data->rpm = 9999;
                    break;
                }
                else
                {
                    rpm_retry_count++;
                }
            }

            delay(10);
        }

        vTaskDelay(3000 / portTICK_PERIOD_MS);
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