#include <Widget.h>

// void WidgetMgr::InitBTTask(void *param)
// {
//     WidgetMgr* self = static_cast<WidgetMgr*>(param);
//     esp_task_wdt_add(NULL);
//     esp_task_wdt_init(60, true);
//     esp_task_wdt_reset();

//     UpdateOBDStatus("BT Init success");

//     // Bluetooth 초기화 후 지연
//     esp_task_wdt_reset(); 
//     vTaskDelay(pdMS_TO_TICKS(100));

//     if(NotifyOBDConnect())
//     {
//         esp_task_wdt_reset();
//         vTaskDelay(pdMS_TO_TICKS(100));
//     }


//     esp_task_wdt_reset(); 
//     vTaskDelay(pdMS_TO_TICKS(100));
//     esp_task_wdt_delete(NULL);
//     vTaskDelete(NULL);
// }

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

    lv_label_set_text(ui_cpu_usage, cpu);
    lv_label_set_text(ui_ram_usage, ram);
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

void WidgetMgr::initWidget(TaskHandle_t *bt_handler, TaskHandle_t *usage_handler)
{
    if(not serial_bt.isReady())
    {
        UpdateOBDStatus("BT Init failed");
        return;
    }

    // xTaskCreate(InitBTTask, "initBTTask", 4096, this, 1, bt_handler);
    Serial.println("[WidgetMgr] : Init BT <-> OBD asynchronously");
    xTaskCreate(CalculateCpuRamUsageTask, "CalCpuRam", 4096, this, 2, usage_handler);
    Serial.println("[WidgetMgr] : Create CPU/RAM usage calcultaion task by 3sec period");
}

void WidgetMgr::CalculateCpuRamUsageTask(void *param)
{
    WidgetMgr* self = static_cast<WidgetMgr*>(param);
    while (true)
    {
        self->measure_task_time_start();
        self->update_usage();
        self->measure_task_time_end();

        vTaskDelay(pdMS_TO_TICKS(3000)); // 3초마다 업데이트
    }
}