#ifndef __WELCOME__
#define __WELCOME__

#include <Arduino.h>
#include <Global.h>
#include <MP3.h>

class WelcomeMgr
{
    private:

    public:
        WelcomeMgr()
        {
            Serial.println("====WelcomeMgr");
        }
        ~WelcomeMgr()
        {
            Serial.println("~~~~WelcomeMgr");
        }

        void InitWelcome(void);
        static void CheckGoodbyeCondition(void* param);
};

#endif