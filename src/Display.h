#ifndef __DISPLAY__
#define __DISPLAY__

#include <pride_common.h>
#include <lvgl.h>
#include <TFT_eSPI.h>
#include <ui.h>

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define SCREENBUFFER_SIZE_PIXELS 7680

TFT_eSPI tft = TFT_eSPI(SCREEN_WIDTH, SCREEN_HEIGHT);

class DisplayMgr
{
    private:
        lv_disp_t* disp;
        lv_indev_t* indev;
        lv_color_t buf [SCREENBUFFER_SIZE_PIXELS];
    public:
        DisplayMgr()
        {
            Serial.println("====DisplayMgr");
            String LVGL_Arduino = "Hello Arduino! ";
            LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();
            Serial.println( LVGL_Arduino );
        }

        ~DisplayMgr()
        {
            Serial.println("~~~~DisplayMgr");
        }

        bool initDisplay(int splash_count);
        static void flush_display(lv_display_t *disp, const lv_area_t *area, uint8_t *pixelmap);
        static uint32_t my_tick_get_cb(void);
        void UpdateOBDStatus(char *status);
};

#endif