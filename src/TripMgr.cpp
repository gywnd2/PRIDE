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

void TripMgr::GetDistance(char* buf)
{
    ObdData data = obd.GetObdData();
    snprintf(buf, 9, "%d", data.distance);
    Serial.printf("[TripMgr::GetDistance] Trip distance %d\n", data.distance);
}

void TripMgr::GetFuelConsumption(char* buf)
{
    ObdData data = obd.GetObdData();
    float fuel_used_liter = 0.0;

    if (data.maf_rate > 0) {
        float fuelRateLph = (data.maf_rate * 3600.0) / (14.7 * 745.0);
        fuel_used_liter += (fuelRateLph * (end_time - start_time)/1000.0) / 3600.0;
    }

    snprintf(buf, 9, "%.2f", fuel_used_liter);
    Serial.printf("[TripMgr::GetFuelConsumption] Used fuel in liter %f\n", fuel_used_liter);
}