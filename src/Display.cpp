#include <Display.h>
#include <lvgl.h>

void DisplayMgr::InitDisplay()
{
    tft.begin();          /* TFT init */
    Serial.println("[DisplayMgr] TFT initialized.");
    tft.setRotation( 3 ); /* Landscape orientation, flipped */
    Serial.println("[DisplayMgr] TFT rotation set to 3.");
    ///////////////////



    ////////////////////
    lv_init();
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

    ui_init();
    Serial.println("[DisplayMgr] UI initialized."); 

    xTaskCreate(updateDisplay, "UpdateDisplay", 8192, this, 3, NULL);
    Serial.println("[DisplayMgr] UpdateDisplay task created.");


}

void DisplayMgr::updateDisplay(void *param)
{
    while(true)
    {
        lv_timer_handler();
        vTaskDelay(pdMS_TO_TICKS(5));
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

void DisplayMgr::UpdateOBDStatus(char *status)
{
    lv_label_set_text(ui_obd_status, status);
}