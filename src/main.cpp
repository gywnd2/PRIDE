#include <main.h>

void setup ()
{
    Serial.begin( 115200 ); /* prepare for possible serial debug */
    serial_bt.begin("PRIDE_ESP32", true);

    storage.InitStorage();
    storage.UpdateSplashEEPROM();
    display.InitDisplay();
    dfp.InitMp3();
    welcome.InitWelcome();
    widget.initWidget(bt_task_handler, cal_cpu_ram_handler);
    obd.InitOBD();

    xTaskCreate(welcome.CheckGoodbyeCondition, "CheckGoodbyeCondition", 2048, &welcome, 1, welcome_handler);
    xTaskCreate(UpdateGauge, "UpdateGauge", 2048, NULL, 2, NULL);

    Serial.println( "Setup done" );
}

void loop ()
{
    vTaskDelay(pdMS_TO_TICKS(5));
}

void UpdateGauge(void* param)
{
    while(true)
    {
        if(obd.IsOBDInitialized() == false || isLvglInit == false)
        {
            Serial.println("[Main] OBD or LVGL not initialized yet.");
            continue;
        }

        ObdData data = obd.GetObdData();
        char buffer[8];

        memset(buffer, 0, sizeof(buffer));
        sprintf(buffer, "%u", data.voltage);
        lv_label_set_text(ui_Bar1, buffer);

        memset(buffer, 0, sizeof(buffer));
        sprintf(buffer, "%u", data.coolant);
        lv_label_set_text(ui_Bar2, buffer);

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}