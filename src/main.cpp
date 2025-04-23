#include <main.h>
#include <pride_common.h>

void setup ()
{
    Serial.begin( 115200 ); /* prepare for possible serial debug */
    serial_bt.begin("PRIDE_ESP32", true);
    
    storage.InitStorage();
    storage.UpdateSplashEEPROM();
    display.initDisplay(storage);
    obd.InitOBD(serial_bt);
    // dfp.initMp3();
    // welcome.InitWelcome(obd, dfp);
    // if(storage.GetSplashCount() == 2)
    // {
    //     widget.initWidget(display, serial_bt.available(), bt_task_handler, cal_cpu_ram_handler);
    // }

    Serial.println( "Setup done" );
}

void loop ()
{
    //lv_timer_handler(); /* let the GUI do its work */
    delay(5);
    UpdateGauge(obd);
}

void UpdateGauge(OBDMgr &obd)
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