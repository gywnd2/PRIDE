#include <WelcomeMgr.h>

void WelcomeMgr::InitWelcome(void)
{
    Serial.println("[WelcomeMgr] Init");
    dfp.PlaySound(WELCOME_TRACK_NUM);

    xTaskCreate(CheckGoodbyeCondition, "CheckGoodbyeCondition", 2048, this, 1, welcome_handler);
}

void WelcomeMgr::CheckGoodbyeCondition(void* param)
{
    WelcomeMgr* self = static_cast<WelcomeMgr*>(param);
    if(self == NULL)
    {
        Serial.println("[WelcomeMgr] CheckGoodbyeCondition param is NULL.");
        vTaskDelete(NULL);
        return;
    }

    unsigned long start_time = millis();

    while(true)
    {
        static bool goodbye_played = false;
        if(goodbye_played)
        {
            vTaskDelete(NULL);
            return;
        }

        unsigned long current_time = millis();
        if(current_time - start_time >= LOG_INTERVAL) // 10초 후 종료
        {
            Serial.printf("[WelcomeMgr] CheckGoodbyeCondition / goodbye_played %d\n", goodbye_played);
            start_time = millis();
        }

        ObdData data = obd.GetObdData();

        if(100 <= data.rpm && data.rpm <= 7000)
        {
            continue;
        }

        if(obd.GetOBDStatus() == OBD_DISCONNECTED)
        {
            NotifyPlaySound(GOODBYE_TRACK_NUM);
            goodbye_played = true;
        }

        vTaskDelay(pdTICKS_TO_MS(100));
    }

}