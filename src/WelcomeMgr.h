#ifndef __WELCOME__
#define __WELCOME__

#include <Arduino.h>
#include <DataType.h>
#include <OBD.h>

class WelcomeMgr
{
    private:
        OBDMgr *obd;
        Mp3Mgr *dfp;

    public:
        WelcomeMgr()             
        {
            Serial.println("====WelcomeMgr");
        }
        ~WelcomeMgr()
        {
            Serial.println("~~~~WelcomeMgr");
        }

        void InitWelcome(OBDMgr &obd_mgr, Mp3Mgr &dfp_mgr);
        void CheckGoodbyeCondition(void);
};

#endif