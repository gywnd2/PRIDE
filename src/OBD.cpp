
#include <OBD.h>

void OBDMgr::InitOBD(void)
{
    Serial.println("[OBDMgr] Connect OBD task started");

    UpdateOBDStatus("BT Init success");

    // Bluetooth 초기화 후 지연
    vTaskDelay(pdMS_TO_TICKS(100));
    Serial.println("[OBDMgr] BT delay success");

    if(NotifyConnectOBD(obd_addr))
    {
         Serial.println("[OBDMgr] BT Connect success");
         if(myELM327.begin(RequestBTSerial(), true, 2000))
         {
             Serial.println("[OBDMgr] OBD Service success");
             xTaskCreate(Query30SecData, "Query30SecData", 2048, this, 3, &query_coolant_voltage_handler);
             Serial.println("[OBDMgr] Query30SecData task created");
             xTaskCreate(QueryRPM, "Query3SecRPM", 2048, this, 2, &query_rpm);
             Serial.println("[OBDMgr] QueryRPM task created");
         }
         else
         {
             Serial.println("[OBDMgr] OBD Service Failed");
             UpdateOBDStatus("OBD Service Failed");
         }
    }
    else
    {
        Serial.println("[OBDMgr] BT Connect Failed");
        UpdateOBDStatus("BT Connect Failed");
    }

    obd_init = true;
    esp_task_wdt_delete(NULL);
}

bool OBDMgr::IsOBDInitialized(void)
{
    return obd_init;
}

void OBDMgr::QueryCoolant(uint16_t &coolant_temp)
{
    while(true)
    {
        Serial.println("[OBDMgr] QueryCoolant");
        float coolant = myELM327.engineCoolantTemp();
        if(myELM327.nb_rx_state == ELM_SUCCESS)
        {
            coolant_temp = (uint16_t)coolant;
            Serial.println("[OBDMgr] coolant level set to "+(String)coolant_temp);
            break;
        }
        else if(myELM327.nb_rx_state == ELM_NO_DATA)
        {
            coolant_temp = 9999;
            Serial.println("[OBDMgr] coolant level no data");
            dfp.PlaySound(GOODBYE_TRACK_NUM);
            delay(6000);
            break;
        }
        else
        {
            Serial.println("[OBDMgr] Unexpected rx state in query coolant "+String(myELM327.nb_rx_state));
        }
        delay(10);
    }
}

void OBDMgr::QueryVoltage(uint16_t &voltage_level)
{
    while(true)
    {
        Serial.println("[OBDMgr] QueryVoltage");
        float voltage = myELM327.batteryVoltage();
        if(myELM327.nb_rx_state == ELM_SUCCESS)
        {
            voltage_level = (uint16_t)voltage;
            Serial.println("[OBDMgr] voltage level set to "+(String)voltage_level);
            break;
        }
        else if(myELM327.nb_rx_state == ELM_NO_DATA)
        {
            voltage_level = 9999;
            Serial.println("[OBDMgr] voltage level no data");
            dfp.PlaySound(GOODBYE_TRACK_NUM);
            delay(6000);
            break;
        }
        else
        {
            Serial.println("[OBDMgr] Unexpected rx state in query voltage "+String(myELM327.nb_rx_state));
        }
        delay(10);
    }
}

void OBDMgr::Query30SecData(void *param)
{
    OBDMgr* self = static_cast<OBDMgr*>(param);
    ObdData data;

    while(1)
    {
        Serial.println("[OBDMgr] Query30SecData task");
        if(self->obd_busy == true)
        {
            Serial.println("[OBDMgr] OBD is busy. Skip Query30SecData task.");
            continue;
        }

        data = self->GetObdData();

        self->obd_busy = true;
        self->QueryVoltage(data.voltage);
        self->QueryCoolant(data.coolant);
        self->obd_busy = false;

        self->SetVoltageLevel(data.voltage);
        self->SetCoolantTemp(data.coolant);

        esp_task_wdt_delete(NULL);
        vTaskDelay(30000 / portTICK_PERIOD_MS);
    }

}

void OBDMgr::QueryRPM(void *param)
{
    OBDMgr* self = static_cast<OBDMgr*>(param);

    ObdData data;

    while(1)
    {
        Serial.println("[OBDMgr] QueryRPM task");
        if(self->obd_busy == true)
        {
            Serial.println("[OBDMgr] OBD is busy. Skip QueryRPM task.");
            continue;
        }

        int rpm_retry_count = 0;
        self->obd_busy = true;
        while(true)
        {
            data = self->GetObdData();

            float rpm = self->myELM327.rpm();
            if(self->myELM327.nb_rx_state == ELM_SUCCESS)
            {
                rpm_retry_count = 0;
                data.rpm = (uint16_t)rpm;
                Serial.println("[OBDMgr] RPM set to "+(String)data.rpm);
                break;
            }
            else if(self->myELM327.nb_rx_state == ELM_NO_DATA)
            {
                if(rpm_retry_count == 2)
                {
                    data.rpm = 9999;
                    Serial.println("[OBDMgr] RPM response is invalid. Retry Count "+String(rpm_retry_count));
                    break;
                }
                else
                {
                    rpm_retry_count++;
                }
            }
            else
            {
                Serial.println("[OBDMgr] Unexpected rx state in query rpm "+String(self->myELM327.nb_rx_state));
            }

            delay(10);
        }

        self->obd_busy = false;
        self->SetRPM(data.rpm);
        esp_task_wdt_delete(NULL);
        vTaskDelay(3000 / portTICK_PERIOD_MS);
    }

}

ObdData OBDMgr::GetObdData(void)
{
    return obd_data;
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