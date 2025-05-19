#include <OBD.h>



void OBDMgr::InitOBD(void)
{
    Serial.println("[OBDMgr] Connect OBD task started");

    SetOBDStatus(BT_INIT_SUCCESS);
    // Bluetooth 초기화 후 지연
    vTaskDelay(pdMS_TO_TICKS(100));
    Serial.println("[OBDMgr] BT delay success");

    xTaskCreatePinnedToCore(ConnectBTTask, "ConnectBTTask", 2048, this, 2, NULL, 1);
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

#ifndef OBD_SIMUL_MODE
    NotifyConnectOBD(self->obd_addr);

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
#endif
    Serial.println("[OBDMgr] ELM327 initialized successfully.");
    xTaskCreatePinnedToCore(QueryOBDData, "QueryOBDData", 2048, self, 3, &(self->query_obd_data_task), 1);
    Serial.println("[OBDMgr] QueryOBDData task created successfully.");
    self->SetOBDStatus(OBD_CONNECTED);
    vTaskDelete(NULL);
}

void OBDMgr::QueryCoolant(uint16_t &coolant_temp)
{
    Serial.println("[OBDMgr] QueryCoolant");
#ifdef OBD_SIMUL_MODE
    long query_start_time = millis();
    long curr_time = 0;

    while(curr_time - query_start_time <= OBD_SIMUL_QUERY_TIME)
    {
        //vTaskDelay(10);
        curr_time = millis();
    }

    coolant_temp = rand() % (150 - 0 + 1) + 0;
    Serial.printf("[OBDMgr] OBD Simul mode / coolant set to %d\n", coolant_temp);
#else
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

        delay(100);
    }
#endif
}

void OBDMgr::QueryVoltage(uint16_t &voltage_level)
{
    Serial.println("[OBDMgr] QueryVoltage");
#ifdef OBD_SIMUL_MODE
    long query_start_time = millis();
    long curr_time = 0;

    while(curr_time - query_start_time <= OBD_SIMUL_QUERY_TIME)
    {
        //vTaskDelay(10);
        curr_time = millis();
    }

    voltage_level = rand() % (18 - 6 + 1) + 6;
    Serial.printf("[OBDMgr] OBD Simul mode / voltage set to %d\n", voltage_level);
#else
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

        delay(100);
    }
#endif
}

void OBDMgr::QueryRPM(uint16_t &rpm_value)
{
    Serial.println("[OBDMgr] QueryRPM");
    int rpm_retry_count = 0;

#ifdef OBD_SIMUL_MODE
    long query_start_time = millis();
    long curr_time = 0;

    while(curr_time - query_start_time <= OBD_SIMUL_QUERY_TIME)
    {
        vTaskDelay(10);
        curr_time = millis();
    }

    rpm_value = rand() % (6000 - 1000 + 1) + 1000;
    Serial.printf("[OBDMgr] OBD Simul mode / rpm set to %d\n", rpm_value);
#else
    while(true)
    {
        float rpm = myELM327    .rpm();
        if(myELM327.nb_rx_state == ELM_SUCCESS)
        {
            rpm_retry_count = 0;
            rpm_value = (uint16_t)rpm;
            break;
        }
        else if(myELM327.nb_rx_state == ELM_NO_DATA)
        {
            if(rpm_retry_count == 3)
            {
                rpm_value = OBD_QUERY_INVALID_RESPONSE;
                Serial.println("[OBDMgr] RPM response is invalid. Retry Count "+String(rpm_retry_count));
                SetOBDStatus(OBD_DISCONNECTED);
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

        delay(100);
    }
#endif
}

void OBDMgr::QueryDistAfterErrorClear(uint16_t &distance)
{
    Serial.println("[OBDMgr] QueryDistAfterErrorClear");
#ifdef OBD_SIMUL_MODE
    long query_start_time = millis();
    long curr_time = 0;

    while(curr_time - query_start_time <= OBD_SIMUL_QUERY_TIME)
    {
        vTaskDelay(10);
        curr_time = millis();
    }

    distance = rand() % (6000 - 1000 + 1) + 1000;
    Serial.printf("[OBDMgr] OBD Simul mode / distance set to %d\n", distance);
#else
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

        delay(100);
    }
#endif
}

void OBDMgr::QueryMaf(float &fuel_consumption)
{
    Serial.println("[OBDMgr] QueryMaf");
    while(true)
    {
        float maf_rate = myELM327.mafRate();
        if(myELM327.nb_rx_state == ELM_SUCCESS)
        {
            fuel_consumption = (uint16_t)maf_rate;
            break;
        }
        else if(myELM327.nb_rx_state == ELM_NO_DATA)
        {
            fuel_consumption = OBD_QUERY_INVALID_RESPONSE;
            break;
        }
        else if(myELM327.nb_rx_state == ELM_GETTING_MSG)
        {
            // Do nothing, wait for the response
        }
        else
        {
            Serial.println("[OBDMgr] Unexpected rx state in query maf "+String(myELM327.nb_rx_state));
        }

        delay(100);
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

void OBDMgr::SetMafRate(float val)
{
    Serial.println("[OBDMgr] Set maf_rate consumption to "+String(val));
    obd_data.maf_rate = val;
}

void OBDMgr::SetOBDStatus(int status)
{
    Serial.println("[OBDMgr] Set OBD status to "+String(status));
    obd_status = status;
}

int OBDMgr::GetOBDStatus(void)
{
#ifdef GOODBYE_TEST
    static int count = 0;
    if(count <= 20000) count++;
    if(count%10000 == 0) Serial.println("[OBDMgr] Get OBD status count "+String(count));
    if(count >= 20000)
    {
        return OBD_DISCONNECTED;
    }
#endif
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
        if (current_time - last_rpm_time >= pdMS_TO_TICKS(2000))
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
        if (current_time - last_30sec_time >= pdMS_TO_TICKS(60000))
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
                self->SetVoltageLevel(data.voltage);
                self->QueryCoolant(data.coolant);
                self->SetCoolantTemp(data.coolant);
                self->QueryDistAfterErrorClear(data.distance);
                self->SetDistance(data.distance);
                self->obd_busy = false;
            }

            last_30sec_time = current_time; // 마지막 30초 쿼리 시간 갱신
        }

        /*
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
                //self->QueryDistAfterErrorClear(data.distance);
                //self->SetDistance(data.distance);
                //TODO : calculate avg. maf_rate consumption
                //self->QueryMaf(data.maf_rate);
                //self->SetMafRate(data.maf_rate);

                self->obd_busy = false;
            }

            last_1min_12sec_time = current_time;
        }
        */

        if(self->GetOBDStatus() == OBD_DISCONNECTED)
        {
            Serial.println("[OBDMgr] OBD is disconnected. Delete data query task.");
            vTaskDelete(NULL);
            return;
        }

        // 태스크 주기 대기
        vTaskDelay(pdMS_TO_TICKS(100)); // 100ms 대기
    }
}