#ifndef __TRIP__
#define __TRIP__

#include <Arduino.h>
#include <pride_common.h>
#include <Global.h>

class TripMgr
{
    private:
        unsigned long start_time;
        unsigned long end_time;
        uint32_t distance;
        float fuel_consumption;

    public:
        TripMgr() : start_time(0),
                    end_time(0),
                    distance(0),
                    fuel_consumption(0)
        {
            Serial.println("====TripMgr");
        }
        ~TripMgr()
        {
            Serial.println("~~~~TripMgr");
        }

        void InitTrip(void);
        void SetStartTime(unsigned long time);
        void SetEndTime(unsigned long time);
        void GetElapsedTime(char* buf);
        void GetDistance(char* buf);
        void GetFuelConsumption(char* buf);
};

#endif