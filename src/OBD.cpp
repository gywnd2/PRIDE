#include <OBD.h>



void OBDMgr::InitOBD(void)
{
    Serial.println("[OBDMgr] Connect OBD task started");

    SetOBDStatus(BT_INIT_SUCCESS);
    // Bluetooth 초기화 후 지연
    vTaskDelay(pdMS_TO_TICKS(100));
    Serial.println("[OBDMgr] BT delay success");

    xTaskCreate(ConnectBTTask, "ConnectBTTask", 4096, this, 2, NULL);
}

void OBDMgr::ConnectBTTask(void *param)
{
    esp_task_wdt_delete(NULL);

    OBDMgr* self = static_cast<OBDMgr*>(param);
    if(self == NULL)
    {
        Serial.println("[OBDMgr] ConnectBTTask param is NULL.");
        vTaskDelete(NULL);
        return;
    }

    Serial.println("[OBDMgr] ConnectBTTask started");

    self->SetOBDStatus(BT_CONNECTING);
    NotifyConnectOBD(self->obd_addr);

    //vTaskDelete(NULL);
    //return;

    int retry_count = 0;
    unsigned long last_check_time = millis();
    while (true)
    {
        if (millis() - last_check_time >= BT_CONNECTION_CHECK_INTERVAL) { // 1초마다 호출
            if (!serial_bt.connected()) {
                Serial.println("[OBDMgr] Bluetooth disconnected.");
                self->SetOBDStatus(BT_CONNECT_FAILED);
                vTaskDelete(NULL);
                return;
            }
            else
            {
                break;
            }
            last_check_time = millis();
        }

        vTaskDelay(pdMS_TO_TICKS(100)); // 100ms 대기
    }

    Serial.println("[OBDMgr] Bluetooth connected successfully.");

    // OBD 초기화
    retry_count = 0;
    self->myELM327.begin(RequestBTSerial(), true, 2000);

    while(!self->myELM327.connected)
    {
        Serial.println("[OBDMgr] Waiting for ELM327 initialization...");
        retry_count++;
        self->SetOBDStatus(OBD_INIT_SUCCESS);

        if(retry_count > 10) {
            Serial.println("[OBDMgr] ELM327 initialization timeout.");
            self->SetOBDStatus(OBD_INIT_FAILED);
            vTaskDelete(NULL);
            return;
        }
        vTaskDelay(pdMS_TO_TICKS(1000)); // 1초 대기
    }

    Serial.println("[OBDMgr] ELM327 initialized successfully.");
    xTaskCreate(QueryOBDData, "QueryOBDData", 4096, self, 3, &(self->query_obd_data_task));
    Serial.println("[OBDMgr] QueryOBDData task created successfully.");
    self->SetOBDStatus(OBD_CONNECTED);
    vTaskDelete(NULL);

}

void OBDMgr::QueryCoolant(uint16_t &coolant_temp)
{
    Serial.println("[OBDMgr] QueryCoolant");
    while(true)
    {
        float coolant = myELM327.engineCoolantTemp();
        if(myELM327.nb_rx_state == ELM_SUCCESS)
        {
            coolant_temp = (uint16_t)coolant;
            break;
        }
        else if(myELM327.nb_rx_state == ELM_NO_DATA)
        {
            coolant_temp = OBD_QUERY_INVALID_RESPONSE;
            break;
        }
        else if(myELM327.nb_rx_state == ELM_GETTING_MSG)
        {
            // Do nothing, wait for the response
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
    Serial.println("[OBDMgr] QueryVoltage");
    while(true)
    {
        float voltage = myELM327.batteryVoltage();
        if(myELM327.nb_rx_state == ELM_SUCCESS)
        {
            voltage_level = (uint16_t)voltage;
            break;
        }
        else if(myELM327.nb_rx_state == ELM_NO_DATA)
        {
            voltage_level = OBD_QUERY_INVALID_RESPONSE;
            break;
        }
        else if(myELM327.nb_rx_state == ELM_GETTING_MSG)
        {
            // Do nothing, wait for the response
        }
        else
        {
            Serial.println("[OBDMgr] Unexpected rx state in query voltage "+String(myELM327.nb_rx_state));
        }
        delay(10);
    }
}

void OBDMgr::QueryRPM(uint16_t &rpm_value)
{
    Serial.println("[OBDMgr] QueryRPM");
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
                rpm_value = OBD_QUERY_INVALID_RESPONSE;
                Serial.println("[OBDMgr] RPM response is invalid. Retry Count "+String(rpm_retry_count));
                break;
            }
            else
            {
                rpm_retry_count++;
            }
        }
        else if(myELM327.nb_rx_state == ELM_GETTING_MSG)
        {
            // Do nothing, wait for the response
        }
        else
        {
            Serial.println("[OBDMgr] Unexpected rx state in query rpm "+String(myELM327.nb_rx_state));
        }

        delay(10);
    }
}

void OBDMgr::QueryDistAfterEcuBoot(uint16_t &distance)
{
    Serial.println("[OBDMgr] QueryDistAfterEcuBoot");
    while(true)
    {
        uint16_t dist = myELM327.distSinceCodesCleared();
        if(myELM327.nb_rx_state == ELM_SUCCESS)
        {
            distance = (uint16_t)dist;
            break;
        }
        else if(myELM327.nb_rx_state == ELM_NO_DATA)
        {
            distance = OBD_QUERY_INVALID_RESPONSE;
            break;
        }
        else if(myELM327.nb_rx_state == ELM_GETTING_MSG)
        {
            // Do nothing, wait for the response
        }
        else
        {
            Serial.println("[OBDMgr] Unexpected rx state in query distance "+String(myELM327.nb_rx_state));
        }
        delay(10);
    }
}

ObdData OBDMgr::GetObdData(void)
{
    return obd_data;
}

void OBDMgr::SetCoolantTemp(uint16_t val)
{
    Serial.println("[OBDMgr] Set Coolant to "+String(val));
    obd_data.coolant = val;
}

void OBDMgr::SetVoltageLevel(uint16_t val)
{
    Serial.println("[OBDMgr] Set Voltage to "+String(val));
    obd_data.voltage = val;
}

void OBDMgr::SetRPM(uint16_t val)
{
    Serial.println("[OBDMgr] Set RPM to "+String(val));
    obd_data.rpm = val;
}

void OBDMgr::SetDistance(uint16_t val)
{
    Serial.println("[OBDMgr] Set distance to "+String(val));
    obd_data.distance = val;
}

void OBDMgr::SetOBDStatus(int status)
{
    Serial.println("[OBDMgr] Set OBD status to "+String(status));
    obd_status = status;
}

int OBDMgr::GetOBDStatus(void)
{
    //TEST : goodbye after 3sec
    static int count = 0;
    if(count <= 3000) count++;
    Serial.println("[OBDMgr] Get OBD status count "+String(count));
    if(count >= 3000)
    {
        return OBD_DISCONNECTED;
    }

    return obd_status;
}

void OBDMgr::QueryOBDData(void *param)
{
    OBDMgr* self = static_cast<OBDMgr*>(param);
    if(self == NULL)
    {
        Serial.println("[OBDMgr] QueryOBDData param is NULL.");
        vTaskDelete(NULL);
        return;
    }

    ObdData data;

    unsigned long last_rpm_time = millis();      // 마지막 RPM 쿼리 시간
    unsigned long last_30sec_time = millis();   // 마지막 30초 쿼리 시간
    unsigned long last_1min_12sec_time = millis();

    while (true)
    {
        unsigned long current_time = millis();

        // 3초마다 RPM 쿼리
        if (current_time - last_rpm_time >= 3000)
        {
            Serial.println("[OBDMgr] QueryOBDData - RPM Task");

            if(self->obd_busy)
            {
                Serial.println("[OBDMgr] OBD is busy. Skip RPM query.");
            }
            else
            {
                self->obd_busy = true;
                self->QueryRPM(data.rpm);
                self->SetRPM(data.rpm);
                self->obd_busy = false;
            }

            last_rpm_time = current_time; // 마지막 RPM 쿼리 시간 갱신
        }

        // 30초마다 Voltage와 Coolant 쿼리
        if (current_time - last_30sec_time >= 30000)
        {
            Serial.println("[OBDMgr] QueryOBDData - Voltage and Coolant Task");

            if (self->obd_busy)
            {
                Serial.println("[OBDMgr] OBD is busy. Skip Voltage and Coolant query.");
            }
            else
            {
                self->obd_busy = true;
                self->QueryVoltage(data.voltage);
                self->QueryCoolant(data.coolant);
                self->SetVoltageLevel(data.voltage);
                self->SetCoolantTemp(data.coolant);
                self->obd_busy = false;
            }

            last_30sec_time = current_time; // 마지막 30초 쿼리 시간 갱신
        }

        if (current_time - last_1min_12sec_time >= 72000)
        {
            Serial.println("[OBDMgr] QueryOBDData - Fuel Consumption Task");

            if (self->obd_busy)
            {
                Serial.println("[OBDMgr] OBD is busy. Skip distance query.");
            }
            else
            {
                self->obd_busy = true;
                self->QueryDistAfterEcuBoot(data.distance);
                self->SetDistance(data.distance);
                //TODO : calculate avg. fuel consumption

                self->obd_busy = false;
            }
        }

        if(self->myELM327.nb_rx_state == ELM_NO_DATA)
        {
            Serial.println("[OBDMgr] OBD is disconnected. Delete data query task.");
            self->SetOBDStatus(OBD_DISCONNECTED);
            vTaskDelete(NULL);
            return;
        }

        // 태스크 주기 대기
        vTaskDelay(pdMS_TO_TICKS(100)); // 100ms 대기
    }
}