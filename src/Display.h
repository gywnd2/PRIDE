#ifndef __DISPLAY__
#define __DISPLAY__

#include <Arduino.h>
#include <TFT_eSPI.h>
#include <ui.h>
#include <Global.h>
#include <AnimatedGIF.h>

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define SCREENBUFFER_SIZE_PIXELS 240

static TFT_eSPI tft = TFT_eSPI(SCREEN_WIDTH, SCREEN_HEIGHT); // Invoke library, pins defined in User_Setup.h

class DisplayMgr
{
    private:
        AnimatedGIF gif;
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

        void InitDisplay(void);
        static void UpdateDisplay(void* param);
        static void flush_display(lv_display_t *disp, const lv_area_t *area, uint8_t *pixelmap);
        static uint32_t my_tick_get_cb(void);
};

#endif