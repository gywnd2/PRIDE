#ifndef __STORAGE__
#define __STORAGE__

#include "EEPROM.h"

class StorageMgr
{
    private:
    public:
        StorageMgr()
        {
            Serial.println("====StorageMgr");
        }
        ~StorageMgr()
        {
            Serial.println("~~~~StorageMgr");
        }

        bool InitStorage(void);
        void UpdateSplashEEPROM(void);
        int GetSplashCount(void);
};

#endif