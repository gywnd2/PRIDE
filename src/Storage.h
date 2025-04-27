#ifndef __STORAGE__
#define __STORAGE__

#include <Global.h>
#include "EEPROM.h"
#include <SD.h>
#include <SPIFFS.h>

typedef struct {
    File *file;
} lvgl_file_t;

class StorageMgr
{
    private:
        lv_fs_drv_t fs_drv;
        bool initialized = false;

    public:
        StorageMgr()
        {
            Serial.println("====StorageMgr");
        }
        ~StorageMgr()
        {
            Serial.println("~~~~StorageMgr");
        }

        bool InitStorage(void);
        bool IsStorageInitialized(void);
        void UpdateSplashEEPROM(void);
        int GetSplashCount(void);\
        void ListFiles(fs::FS &fs, const char *dirname, uint8_t level);
        static void * LVGL_SD_OPEN_CALLBACK(lv_fs_drv_t * drv, const char * path, lv_fs_mode_t mode);
        static lv_fs_res_t LVGL_SD_READ_CALLBACK(lv_fs_drv_t * drv, void * file_p, void * buf, uint32_t btr, uint32_t * br);
        static lv_fs_res_t LVGL_SD_SEEK_CALLBACK(lv_fs_drv_t * drv, void * file_p, uint32_t pos, lv_fs_whence_t whence);
        static lv_fs_res_t LVGL_SD_CLOSE_CALLBACK(lv_fs_drv_t * drv, void * file_p);
        void RegisterLvglSdFs(void);

        static void * LVGL_SPIFFS_OPEN_CALLBACK(lv_fs_drv_t * drv, const char * path, lv_fs_mode_t mode);
        static lv_fs_res_t LVGL_SPIFFS_READ_CALLBACK(lv_fs_drv_t * drv, void * file_p, void * buf, uint32_t btr, uint32_t * br);
        static lv_fs_res_t LVGL_SPIFFS_SEEK_CALLBACK(lv_fs_drv_t * drv, void * file_p, uint32_t pos, lv_fs_whence_t whence);
        static lv_fs_res_t LVGL_SPIFFS_CLOSE_CALLBACK(lv_fs_drv_t * drv, void * file_p);
        void RegisterLvglSpiffsFs(void);

};

#endif