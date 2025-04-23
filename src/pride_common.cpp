#include <pride_common.h>

void UpdateOBDStatus(char *status)
{
    lv_label_set_text(ui_obd_status, status);
}

void NotifyPlaySound(Mp3Mgr &dfp, int track_num)
{
    dfp.PlaySound(track_num);
}