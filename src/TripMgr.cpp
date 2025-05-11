#include <TripMgr.h>

void TripMgr::InitTrip(void)
{
    Serial.println("[TripMgr] Init TripMgr");
    SetStartTime(millis());
}

void TripMgr::SetStartTime(unsigned long time)
{
    start_time = time;
}

void TripMgr::SetEndTime(unsigned long time)
{
    end_time = time;
}

void TripMgr::GetElapsedTime(char* buf)
{
    unsigned long elapsed_time = end_time - start_time;

    unsigned long elapsed_time_in_second = elapsed_time / 1000;
    unsigned int hour = elapsed_time_in_second / 3600;
    unsigned int minute = (elapsed_time_in_second % 3600) / 60;
    unsigned int sec = elapsed_time_in_second % 60;

    snprintf(buf, 9, "%02u:%02u:%02u", hour, minute, sec);
    Serial.printf("[TripMgr::GetElapsedTime] elapsed time : %d, hour : %d, min : %d, sec : %d -> %s\n",
                    elapsed_time, hour, minute, sec, buf);
}

void TripMgr::CalDistance(void)
{

}

void TripMgr::CalFuelConsumption(void)
{

}