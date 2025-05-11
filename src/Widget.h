#ifndef __WIDGET__
#define __WIDGET__

#include <Arduino.h>
#include <ui.h>
#include "esp_task_wdt.h"
#include <pride_common.h>
#include <Global.h>

class WidgetMgr
{
    private:
        uint32_t last_loop_time;
        uint32_t active_task_time;
        uint16_t voltage_level;
        uint16_t coolant_level;

        float get_cpu_usage(void);
        float get_ram_usage(void);
        void update_usage();
        void measure_task_time_start();
        void measure_task_time_end();
        static void CalculateCpuRamUsageTask(void *param);

        TaskHandle_t* cal_cpu_ram_handler;

    public:
        WidgetMgr() : last_loop_time(0),
                      active_task_time(0),
                      voltage_level(0),
                      coolant_level(0)
        {
            Serial.println("====WidgetMgr");
        }
        ~WidgetMgr()
        {
            Serial.println("~~~~WidgetMgr");
        }

        void InitWidget(void);
        bool isBTInit(void);
};

#endif