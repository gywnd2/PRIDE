#include <pride_common.h>

Mp3Mgr dfp;
StorageMgr storage;
WidgetMgr widget;
OBDMgr obd;
WelcomeMgr welcome;
BluetoothSerial serial_bt;
TaskHandle_t bt_task_handler = NULL;
TaskHandle_t cal_cpu_ram_handler = NULL;
TaskHandle_t welcome_handler = NULL;
TaskHandle_t query_coolant_voltage_handler = NULL;

void setup ()
{
    Serial.begin( 115200 ); /* prepare for possible serial debug */
    serial_bt.begin("PRIDE_ESP32", true);
    
    storage.InitStorage();
    storage.UpdateSplashEEPROM();
    if(dfp.initMp3()) dfp.PlayWelcome();
    if(storage.GetSplashCount() == 2)
    {
        widget.initWidget(serial_bt.available(), &bt_task_handler, &cal_cpu_ram_handler);
    }

    xTaskCreate(obd.Query30SecData, "Query30SecData", 2048, obd., 3, )

    Serial.println( "Setup done" );
}

void loop ()
{
    lv_timer_handler(); /* let the GUI do its work */
    delay(5);

    obd.UpdateOBDData(coolant, voltage, rpm);
    UpdateGauge();
}

void NotifyOBDConnect(BluetoothSerial &bt_serial)
{
    obd.ConnectOBD(bt_serial);
}

void UpdateOBDStatus(char *status)
{
    lv_label_set_text(ui_obd_status, status);
}

void UpdateGauge(char *val)
{
    char buffer[8];
    sprintf(buffer, "%u", voltage);
    lv_label_set_text(ui_Bar1, buffer);
    
    sprintf(buffer, "%u", coolant);
    lv_label_set_text(ui_Bar2, buffer);
}

bool NotifyOBDConnect(void)
{
    return obd.ConnectOBD(serial_bt);
}