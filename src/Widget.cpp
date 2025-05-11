#include <Widget.h>

float WidgetMgr::get_cpu_usage(void)
{
    static uint32_t last_time = 0;
    uint32_t current_time = millis();
    uint32_t elapsed_time = current_time - last_time;

    if (elapsed_time == 0) {
        return 0.0f; // division by zero 방지
    }

    // 활성 Task 시간과 IDLE Task 시간
    float active_time = (float)active_task_time / 1000.0f; // micros -> millis
    float idle_time = (float)elapsed_time - active_time;

    // CPU 사용량 계산 (소수점 1자리 포함)
    float cpu_usage = (active_time * 100.0f) / (float)elapsed_time;

    // 디버깅 로그 출력
    //Serial.printf("elapsed_time: %.1f ms, active_time: %.1f ms, idle_time: %.1f ms, cpu_usage: %.1f%%\n",
    //              (float)elapsed_time, active_time, idle_time, cpu_usage);

    // 값 초기화 및 기록 갱신
    active_task_time = 0; // 다음 계산을 위해 초기화
    last_time = current_time;

    return cpu_usage;
}

float WidgetMgr::get_ram_usage(void)
{
    uint32_t free_heap = heap_caps_get_free_size(MALLOC_CAP_DEFAULT);
    uint32_t total_heap = heap_caps_get_total_size(MALLOC_CAP_DEFAULT);

    if (total_heap == 0) return 0.0f;

    // RAM 사용량 계산 (소수점 1자리 포함)
    float ram_usage = 100.0f * (1.0f - ((float)free_heap / (float)total_heap));

    // 디버깅 로그 출력
    //Serial.printf("free_heap: %u bytes, total_heap: %u bytes, ram_usage: %.1f%%\n", free_heap, total_heap, ram_usage);

    return ram_usage;
}

void WidgetMgr::update_usage()
{
    char cpu[6]; // "100.0%"를 저장하려면 6바이트 필요
    sprintf(cpu, "%.1f%%", get_cpu_usage());

    char ram[6]; // "100.0%"를 저장하려면 6바이트 필요
    sprintf(ram, "%.1f%%", get_ram_usage());

    Serial.printf("[WidgetMgr] : CPU usage: %s, RAM usage: %s\n", cpu, ram);

    UpdateCpuUsage(*cpu);
    UpdateRamUsage(*ram);
}

void WidgetMgr::measure_task_time_start()
{
    last_loop_time = micros();
}

void WidgetMgr::measure_task_time_end()
{
    uint32_t current_time = micros();
    active_task_time += (current_time - last_loop_time);
}

void WidgetMgr::InitWidget(void)
{
    Serial.println("[WidgetMgr] : Init BT <-> OBD asynchronously");
    xTaskCreate(CalculateCpuRamUsageTask, "CalCpuRam", 4096, this, 2, cal_cpu_ram_handler);
    Serial.println("[WidgetMgr] : Create CPU/RAM usage calcultaion task by 3sec period");
}

void WidgetMgr::CalculateCpuRamUsageTask(void *param)
{
    WidgetMgr* self = static_cast<WidgetMgr*>(param);
    if(self == NULL)
    {
        Serial.println("[WidgetMgr] : CalculateCpuRamUsageTask param is NULL.");
        vTaskDelete(NULL);
        return;
    }

    unsigned long start_time = millis();
    esp_task_wdt_delete(NULL);

    while (true)
    {
        unsigned long current_time = millis();
        if(current_time - start_time >= LOG_INTERVAL) // 10초 후 종료
        {
            Serial.println("[WidgetMgr] CheckGoodbyCalculateCpuRamUsageTask");
            start_time = millis();
        }

        self->measure_task_time_start();
        self->update_usage();
        self->measure_task_time_end();

        vTaskDelay(pdMS_TO_TICKS(3000)); // 3초마다 업데이트
    }
}