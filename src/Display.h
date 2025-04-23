#ifndef __DISPLAY__
#define __DISPLAY__

#include <Arduino.h>
#include <lvgl.h>
#include <TFT_eSPI.h>
#include <ui.h>
#include <storage.h>

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define SCREENBUFFER_SIZE_PIXELS 7680

static TFT_eSPI tft = TFT_eSPI(SCREEN_WIDTH, SCREEN_HEIGHT); // Invoke library, pins defined in User_Setup.h

class DisplayMgr
{
    private:
        StorageMgr *storage;
        lv_disp_t* disp;
        lv_indev_t* indev;
        lv_color_t buf [SCREENBUFFER_SIZE_PIXELS];
        
    public:
        DisplayMgr()
        {
            Serial.println("====DisplayMgr");
        }

        ~DisplayMgr()
        {
            Serial.println("~~~~DisplayMgr");
        }

        void initDisplay(StorageMgr &storage);
        static void updateDisplay(void *param);
        static void flush_display(lv_display_t *disp, const lv_area_t *area, uint8_t *pixelmap);
        static uint32_t my_tick_get_cb(void);
        void UpdateOBDStatus(char *status);
};

#endif