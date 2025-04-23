#include <Storage.h>

bool StorageMgr::InitStorage(void)
{
    if(EEPROM.begin(1))
    {
        Serial.println("Initialized EEPROM successfully.");
        return true;
    }
    else
    {
        Serial.println("Failed to initialize EEPROM!");
        return false;
    }
}

void StorageMgr::UpdateSplashEEPROM(void)
{
    int splash_count = EEPROM.read(0);
    switch(splash_count)
    {
        case 0xFF:
            Serial.println("[StorageMgr] No splash history found. Set 1 to EEPROM.");
            EEPROM.write(0, 1);
            EEPROM.commit();
            break;
        case 1:
            EEPROM.write(0, 2);
            Serial.println("[StorageMgr] 1st Boot");
            EEPROM.commit();
            break;
        case 2:
            Serial.println("[StorageMgr] "+(String)splash_count+"nd Boot. Trying to connect OBD");
            EEPROM.write(0, 3);
            EEPROM.commit();
            break;
        default:
            Serial.println("[StorageMgr] Wrong splash count detected!");
            EEPROM.write(0, 0xFF);
            EEPROM.commit();
            break;
    }
}

int StorageMgr::GetSplashCount(void)
{
    return EEPROM.read(0);
}