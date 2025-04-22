#ifndef __STORAGE__
#define __STORAGE__

#include <pride_common.h>
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
        int UpdateSplashEEPROM(void);
        int GetSplashCount(void);
};

#endif