#ifndef __WELCOME__
#define __WELCOME__

#include "pride_common.h"


class WelcomeMgr
{
    private:
        Mp3Mgr &dfp;

    public:
        WelcomeMgr()             
        {
            Serial.println("====WelcomeMgr");
        }
        ~WelcomeMgr()
        {
            Serial.println("~~~~WelcomeMgr");
        }

        bool InitWelcome(void);
        void AttachDfp(Mp3Mgr &mp3);
        void checkGoodbyeCondition(Mp3Mgr &dfp);
};

#endif