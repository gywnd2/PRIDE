#include <MP3Mgr.h>

bool Mp3Mgr::InitMp3(void)
{
    dfpSerial.begin(9600, SERIAL_8N1, DFPLAYER_RX, DFPLAYER_TX);

    if(!dfpSerial.available())
    {
        Serial.println("[Mp3Mgr] Failed to initialize dfp serial.");
    }
    else
    {
        Serial.println("[Mp3Mgr] Initialized dfp serial successfully.");
    }

    if(!dfPlayer.begin(dfpSerial))
    {
        Serial.println("[Mp3Mgr] Failed to initiailize DFPlayer Mini!");
    }
    else
    {
        Serial.println("[Mp3Mgr] Initialized DFPlayer Mini successfully.");
        dfPlayer.volume(SOUND_VOLUME);
    }

    return true;
}

void Mp3Mgr::PlaySound(int track_num)
{
    Serial.println("[Mp3Mgr] Play track num "+(String)track_num);
    dfPlayer.play(track_num);
    delay(6000);
}