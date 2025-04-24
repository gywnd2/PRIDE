#include <main.h>

void setup ()
{
    Serial.begin( 115200 ); /* prepare for possible serial debug */
    serial_bt.begin("PRIDE_ESP32", true);
    
    storage.InitStorage();
    storage.UpdateSplashEEPROM();
    display.InitDisplay();
    obd.InitOBD();
    dfp.InitMp3();
    welcome.InitWelcome();
    if(storage.GetSplashCount() == 2)
    {
        widget.initWidget(bt_task_handler, cal_cpu_ram_handler);
    }

    Serial.println( "Setup done" );
}

void loop ()
{
    vTaskDelay(pdMS_TO_TICKS(5));
    UpdateGauge();
}

void UpdateGauge(void)
{
    ObdData data = obd.GetObdData();
    char buffer[8];
    
    memset(buffer, 0, sizeof(buffer));
    sprintf(buffer, "%u", data.voltage);
    lv_label_set_text(ui_Bar1, buffer);
    
    memset(buffer, 0, sizeof(buffer));
    sprintf(buffer, "%u", data.coolant);
    lv_label_set_text(ui_Bar2, buffer);
}