#include <pride_common.h>

bool InitWelcome(void);
void AttachDfp(Mp3Mgr &mp3);
void checkGoodbyeCondition(Mp3Mgr &dfp);
{
    static bool goodbye_played = false;
    if(goodbye_played) return;

    if(100 <= rpm && rpm <= 7000) 
    {
        Serial.println("RPM valid : "+String(rpm));
        return;
    }

    static int rpm_invalid_count = 0;
    for(rpm_invalid_count; rpm_invalid_count < RPM_REQ_RETRY_MAX; rpm_invalid_count++)
    {
        rpm_response = myELM327.rpm();
        while(myELM327.nb_rx_state != ELM_SUCCESS)
        {
            rpm_response = myELM327.rpm();
            if(myELM327.nb_rx_state == ELM_NO_DATA) break;
        }
        if(myELM327.nb_rx_state == ELM_SUCCESS)
        {
            Serial.println("RPM is valid. stop retry");
            break;
        }
        
        delay(500);
        Serial.println("RPM response is invalid. Retry Count "+String(rpm_invalid_count));
    }

    if(rpm_invalid_count == RPM_REQ_RETRY_MAX)                                                                                                                                                         
    {
        Serial.println("RPM response seems like engine turned off. Play Goodbye sound");
        dfPlayer.play(GOODBYE_TRACK_NUM);
        delay(6000);
        goodbye_played = true;
    } 
    else 
    {
        Serial.println("RPM response got normal. Init rpm retry count");
        rpm_invalid_count = 0;
    }
}