#include <WelcomeMgr.h>

void WelcomeMgr::InitWelcome(void)
{
    Serial.println("[WelcomeMgr] Init");
    dfp.PlaySound(WELCOME_TRACK_NUM);
}

void WelcomeMgr::CheckGoodbyeCondition(void)
{
    static bool goodbye_played = false;
    if(goodbye_played) return;

    ObdData data = obd.GetObdData();

    if(100 <= data.rpm && data.rpm <= 7000) 
    {
        Serial.println("RPM valid : "+String(data.rpm));
        return;
    }

    if(data.rpm == 9999)                                                                                                                                                         
    {
        Serial.println("[WelcomeMgr] RPM response seems like engine turned off. Play Goodbye sound");
        NotifyPlaySound(GOODBYE_TRACK_NUM);
        delay(6000);
        goodbye_played = true;
    }
}