#include <Display.h>
#include <SD.h>
#include <Global.h>
#include <esp_heap_caps.h>

void print_lvgl_fs_drivers()
{
    Serial.println("[LVGL FS] 등록된 파일 시스템 드라이버 목록:");

    bool found = false;
    for (char letter = 'A'; letter <= 'Z'; letter++) {
        lv_fs_drv_t * drv = lv_fs_get_drv(letter);
        if (drv) {
            Serial.printf("  - 글자: %c:/ , drv ptr: 0x%p\n", letter, drv);
            found = true;
        }
    }
    for (char letter = '0'; letter <= '9'; letter++) {
        lv_fs_drv_t * drv = lv_fs_get_drv(letter);
        if (drv) {
            Serial.printf("  - 글자: %c:/ , drv ptr: 0x%p\n", letter, drv);
            found = true;
        }
    }

    if (!found) {
        Serial.println("[LVGL FS] 등록된 드라이버가 없습니다.");
    }
}

/*
lv_obj_t *img_obj;  // 이미지 객체

// BMP 파일을 SD 카드에서 읽어 LVGL에 표시하는 함수
void display_bmp_from_sd(const char *filename) {
    File bmpFile = SD.open(filename);
    if (!bmpFile) {
        Serial.println("파일을 열 수 없습니다.");
        return;
    }

    // LVGL 이미지 객체 생성
    lv_img_dsc_t img_dsc;
    img_dsc.header.w = 320;  // 이미지 가로 크기 (필요에 따라 조정)
    img_dsc.header.h = 240;  // 이미지 세로 크기 (필요에 따라 조정)

    uint32_t image_size = bmpFile.size();
    uint8_t *image_buffer = (uint8_t *)malloc(image_size);  // 이미지를 위한 메모리 버퍼

    if (image_buffer) {
        bmpFile.read(image_buffer, image_size);  // BMP 데이터를 버퍼로 읽기
        lv_img_dsc_t *new_img = (lv_img_dsc_t *)image_buffer;  // 이미지로 캐스팅

        if (!img_obj) {
            img_obj = lv_img_create(lv_scr_act());  // 첫 번째 이미지 객체 생성
        }

        lv_img_set_src(img_obj, new_img);  // LVGL 이미지 객체에 이미지 설정
        free(image_buffer);  // 메모리 해제
    } else {
        Serial.println("메모리 할당 실패");
    }

    bmpFile.close();
}

// 이미지 파일 목록을 순차적으로 읽어 애니메이션처럼 처리
void play_bmp_animation() {
    char filename[25];

    for (int i = 0; i <= 64; i++) {  // frame_000.bmp ~ frame_064.bmp 까지
        snprintf(filename, sizeof(filename), "/frames/frame_%03d.bmp", i);  // 파일 이름 포맷 지정
        display_bmp_from_sd(filename);  // 각 프레임을 SD 카드에서 읽어 화면에 표시
        delay(100);  // 프레임 간 딜레이 (속도 조절)
    }
}
*/


void DisplayMgr::InitDisplay()
{
    tft.begin();          /* TFT init */
    Serial.println("[DisplayMgr] TFT initialized.");
    tft.setRotation( 3 ); /* Landscape orientation, flipped */
    Serial.println("[DisplayMgr] TFT rotation set to 3.");
    lv_init();
    if(not storage.IsStorageInitialized())
    {
        Serial.println("[DisplayMgr] Storage not initialized yet.");
        return;
    }
    //storage.RegisterLvglSdFs();
    //storage.RegisterLvglSpiffsFs();
    Serial.println("[DisplayMgr] LVGL initialized.");

    disp = lv_display_create(SCREEN_WIDTH, SCREEN_HEIGHT);
    Serial.println("[DisplayMgr] LVGL display created.");
    lv_display_set_buffers(disp, buf, NULL, SCREENBUFFER_SIZE_PIXELS * sizeof(lv_color_t), LV_DISPLAY_RENDER_MODE_PARTIAL);
    Serial.println("[DisplayMgr] LVGL display buffers set.");
    lv_display_set_flush_cb(disp, flush_display);
    Serial.println("[DisplayMgr] LVGL display flush callback set.");

    indev = lv_indev_create();
    Serial.println("[DisplayMgr] LVGL input device created.");

    lv_indev_set_type( indev, LV_INDEV_TYPE_POINTER );
    Serial.println("[DisplayMgr] LVGL input device type set to pointer.");

    lv_tick_set_cb( my_tick_get_cb );
    Serial.println("[DisplayMgr] LVGL tick callback set.");

    //play_bmp_animation();
    //lv_obj_center(img_obj);

    //TODO : Resolve lack of memory
    printf("Free heap: %d bytes\n", heap_caps_get_free_size(MALLOC_CAP_DEFAULT));

    /*
    lv_obj_t * gif = lv_gif_create(lv_scr_act()); // 현재 스크린에 gif 오브젝트 생성
    const char *gif_path = "/real.gif"; // GIF 파일 경로
    File gif_file = SD.open(gif_path);
    if (!gif_file) {
        Serial.printf("[DisplayMgr] Failed to open GIF file: %s\n", gif_path);
    } else {
        size_t gif_size = gif_file.size();
        Serial.printf("[DisplayMgr] Task Handle: %p\n", xTaskGetCurrentTaskHandle());

        Serial.printf("[DisplayMgr] GIF file opened: %s, size: %d bytes\n", gif_path, gif_size);
        lv_fs_drv_t * drv = lv_fs_get_drv('S');
        if(drv == NULL) {
            Serial.println("[DisplayMgr] Failed to get LVGL file system driver.");


            gif_file.close();
        }
        else {
            Serial.printf("[DisplayMgr] Drive letter S : %d \n", drv->letter);
        }

        print_lvgl_fs_drivers();
        gif_file.close();
        lv_gif_set_src(gif, "S:real.gif");
    }

    // GIF 파일을 lv_gif에 설정
    Serial.printf("[DisplayMgr] GIF source set to: %s\n", gif_path);

    // GIF를 화면 중앙에 위치
    lv_obj_center(gif);

    const lv_image_dsc_t * img_dsc = (const lv_image_dsc_t *)lv_image_get_src(gif);
    if (img_dsc) {
        Serial.printf("[DisplayMgr] GIF width: %d, height: %d\n", img_dsc->header.w, img_dsc->header.h);
    } else {
        Serial.println("[DisplayMgr] Failed to retrieve GIF image descriptor.");
    }
    */

    ui_init();
    isLvglInit = true;
    Serial.println("[DisplayMgr] UI initialized.");

    xTaskCreate(UpdateDisplay, "UpdateDisplay", 4096, this, 1, NULL);
    Serial.println("[DisplayMgr] UpdateDisplay task created.");
}

void DisplayMgr::ShowElapsedTime(void)
{
    trip.SetEndTime(millis());

    char text_buf[9];
    trip.GetElapsedTime(text_buf);
    lv_label_set_text(ui_Time_value, text_buf);
}

void DisplayMgr::ShowTripInfo(lv_timer_t * timer)
{
    lv_scr_load_anim(ui_Goodbye, LV_SCR_LOAD_ANIM_FADE_ON, 2000, 0, true);
    lv_timer_del(timer);
}

void DisplayMgr::ShowGoodbye(lv_timer_t * timer)
{
    lv_scr_load(ui_Init);
    lv_timer_del(timer);
}

void DisplayMgr::UpdateDisplay(void *param)
{
    esp_task_wdt_delete(NULL);
    unsigned long start_time = millis();

    while(true)
    {
        lv_timer_handler();
        vTaskDelay(pdMS_TO_TICKS(5));

        static bool goodbye = false;
        if(obd.GetOBDStatus() == OBD_DISCONNECTED)
        {
            if(not goodbye)
            {
                lv_timer_t* trip_info_timer = lv_timer_create(ShowTripInfo, 0, NULL);
                lv_timer_t* goodbye_timer = lv_timer_create(ShowGoodbye, 12000, NULL);
                ShowElapsedTime();
                //TODO
                //ShowDistance();
                //ShowFuelConsumption();
                goodbye = true;
            }
            continue;
        }

        unsigned long current_time = millis();

        ObdData data = obd.GetObdData();
        char buffer[8];

        lv_bar_set_value(ui_bar_voltage, data.voltage, LV_ANIM_ON);
        lv_bar_set_value(ui_bar_coolant, data.coolant, LV_ANIM_ON);


        // OBD Status
        lv_label_set_text(ui_obd_status, ObdString[obd.GetOBDStatus()].c_str());

        // CPU, RAM
        lv_label_set_text(ui_cpu_usage, cpu_usage);
        lv_label_set_text(ui_ram_usage, ram_usage);

        if(current_time - start_time >= LOG_INTERVAL) // 10초 후 종료
        {
            Serial.printf("[DisplayMgr] UpdateDisplay / OBD Status %d / Voltage %d / Coolant %d / RPM %d\n",
                         obd.GetOBDStatus(), data.voltage, data.coolant, data.rpm);
            start_time = millis();
        }

    }
}

void DisplayMgr::flush_display(lv_display_t *disp, const lv_area_t *area, uint8_t *pixelmap)
{
    uint32_t w = ( area->x2 - area->x1 + 1 );
    uint32_t h = ( area->y2 - area->y1 + 1 );

    if (LV_COLOR_16_SWAP) {
        size_t len = lv_area_get_size( area );
        lv_draw_sw_rgb565_swap( pixelmap, len );
    }

    tft.startWrite();
    tft.setAddrWindow( area->x1, area->y1, w, h );
    tft.pushColors( (uint16_t*) pixelmap, w * h, true );
    tft.endWrite();

    lv_disp_flush_ready( disp );
}

uint32_t DisplayMgr::my_tick_get_cb (void)
{
    return millis();
}