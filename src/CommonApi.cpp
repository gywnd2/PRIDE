#include <CommonApi.h>

void UpdateOBDStatus(int status)
{
    if(not isLvglInit)
    {
        Serial.println("[WidgetMgr] LVGL not initialized yet.");
        return;
    }

    obd.SetOBDStatus(status);
}

void NotifyPlaySound(int track_num)
{
    Serial.println("[NotifyPlaySound] track_num : "+String(track_num));
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

void UpdateCpuUsage(char& val)
{
    if(not isLvglInit)
    {
        Serial.println("[UpdateCpuUsage] LVGL not initialized yet.");
        return;
    }

    strncpy(cpu_usage, &val, sizeof(cpu_usage)-1);
}

void UpdateRamUsage(char& val)
{
    if(not isLvglInit)
    {
        Serial.println("[UpdateRamUsage] LVGL not initialized yet.");
        return;
    }

    strncpy(ram_usage, &val, sizeof(ram_usage)-1);
}