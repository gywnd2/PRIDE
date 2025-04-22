#include <MP3.h>

bool Mp3Mgr::initMp3(void)
{
    dfpSerial.begin(9600, SERIAL_8N1, DFPLAYER_RX, DFPLAYER_TX);

    if(!dfpSerial.available())
    {
        Serial.println("Failed to initialize dfp serial.");
    }
    else
    {
        Serial.println("Initialized dfp serial successfully.");
    }

    if(!dfPlayer.begin(dfpSerial))
    {
        Serial.println("Failed to initiailize DFPlayer Mini!");
    }
    else
    {
        Serial.println("Initialized DFPlayer Mini successfully.");
        dfPlayer.volume(SOUND_VOLUME);
    }

    return true;
}

void Mp3Mgr::PlayWelcome(void)
{
    static bool welcome_played = false;
    if(!welcome_played)
    {
        dfPlayer.play(WELCOME_TRACK_NUM);
        delay(6000);
        welcome_played = true;
    }
}