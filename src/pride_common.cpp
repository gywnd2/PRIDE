#include <pride_common.h>

void UpdateOBDStatus(char *status)
{
    if(not isLvglInit)
    {
        Serial.println("[WidgetMgr] LVGL not initialized yet.");
        return;
    }
    lv_label_set_text(ui_obd_status, status);
}

void NotifyPlaySound(int track_num)
{
    dfp.PlaySound(track_num);
}

bool NotifyConnectOBD(uint8_t remoteAddress[])
{
    return serial_bt.connect(remoteAddress);
}

BluetoothSerial& RequestBTSerial(void)
{
    return serial_bt;
}