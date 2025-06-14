#ifndef __MP3__
#define __MP3__

#include <DFRobotDFPlayerMini.h>
#include <BluetoothSerial.h>
#include <HardwareSerial.h>

#define SOUND_VOLUME 30
#define DFPLAYER_RX 27
#define DFPLAYER_TX 22

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

        bool InitMp3(void);
        void PlaySound(int track_num);
};

#endif