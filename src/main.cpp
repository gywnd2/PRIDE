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
    widget.initWidget(cal_cpu_ram_handler);
    obd.InitOBD();

    xTaskCreate(welcome.CheckGoodbyeCondition, "CheckGoodbyeCondition", 2048, &welcome, 1, welcome_handler);

    Serial.println( "Setup done" );
}

void loop ()
{
    vTaskDelay(pdMS_TO_TICKS(5));
}