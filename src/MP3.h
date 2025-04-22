#ifndef __MP3__
#define __MP3__

#include <DFRobotDFPlayerMini.h>
#include <BluetoothSerial.h>
#include <HardwareSerial.h>

#define SOUND_VOLUME 25
#define DFPLAYER_RX 27
#define DFPLAYER_TX 22
#define WELCOME_TRACK_NUM 1
#define GOODBYE_TRACK_NUM 2

class Mp3Mgr
{
    private:
        HardwareSerial dfpSerial;
        DFRobotDFPlayerMini dfPlayer;
        bool WelcomePlayed;
    
    public:
        Mp3Mgr() : dfpSerial(1), WelcomePlayed(false)
        {
            Serial.println("====Mp3Mgr");
        }
        ~Mp3Mgr()
        {
            Serial.println("~~~~Mp3Mgr");
        }
        
        bool initMp3(void);
        void PlayWelcome(void);
};

#endif