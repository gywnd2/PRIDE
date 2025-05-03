#include <Storage.h>

bool StorageMgr::InitStorage(void)
{
    if(EEPROM.begin(1))
    {
        Serial.println("[StorageMgr] Initialized EEPROM successfully.");
    }
    else
    {
        Serial.println("[StorageMgr] Failed to initialize EEPROM!");
        return false;
    }

    if(SD.begin(5))
    {
        Serial.println("[StorageMgr] Initialized SD card successfully.");
        Serial.println("[StorageMgr] Listing files on SD card:");
        //ListFiles(SD, "/", 0);
    }
    else
    {
        Serial.println("[StorageMgr] Failed to initialize SD card!");
        return false;
    }

    /*
    if(SPIFFS.begin(true))
    {
        Serial.println("[StorageMgr] Initialized SPIFFS successfully.");
    }
    else
    {
        Serial.println("[StorageMgr] Failed to initialize SPIFFS!");
        return false;
    }
    */

    initialized = true;
    return initialized;
}

bool StorageMgr::IsStorageInitialized(void)
{
    return initialized;
}

void StorageMgr::UpdateSplashEEPROM(void)
{
    if(not initialized)
    {
        Serial.println("[StorageMgr] Storage not initialized. Cannot update EEPROM.");
        return;
    }

    int splash_count = EEPROM.read(0);
    switch(splash_count)
    {
        case 0xFF:
            Serial.println("[StorageMgr] No splash history found. Set 1 to EEPROM.");
            EEPROM.write(0, 1);
            EEPROM.commit();
            break;
        case 1:
            EEPROM.write(0, 2);
            Serial.println("[StorageMgr] 1st Boot");
            EEPROM.commit();
            break;
        case 2:
            Serial.println("[StorageMgr] "+(String)splash_count+"nd Boot. Trying to connect OBD");
            EEPROM.write(0, 3);
            EEPROM.commit();
            break;
        default:
            Serial.println("[StorageMgr] Wrong splash count detected!");
            EEPROM.write(0, 0xFF);
            EEPROM.commit();
            break;
    }
}

int StorageMgr::GetSplashCount(void)
{
    return EEPROM.read(0);
}

void StorageMgr::ListFiles(fs::FS &fs, const char *dirname, uint8_t level)
{
    if(not initialized)
    {
        Serial.println("[StorageMgr] Storage not initialized. Cannot list files.");
        return;
    }

    File root = fs.open(dirname);
    Serial.println("[StorageMgr] Listing files in directory: " + String(dirname));
    if (!root) {
        Serial.println("[StorageMgr] Failed to open directory.");
        return;
    }
    if (!root.isDirectory()) {
        Serial.println("[StorageMgr] Not a directory.");
        return;
    }

    File file = root.openNextFile();
    while (file) {
        for (uint8_t i = 0; i < level; i++) {
            Serial.print("  ");
        }
        if (file.isDirectory()) {
            Serial.printf("[DIR] %s\n", file.name());
            String path = String(dirname) + "/" + String(file.name());
            ListFiles(fs, path.c_str(), level + 1);
        } else {
            Serial.printf("[FILE] %s (%d bytes)\n", file.name(), file.size());
        }
        file = root.openNextFile();
    }
}

void * StorageMgr::LVGL_SD_OPEN_CALLBACK(lv_fs_drv_t * drv, const char * path, lv_fs_mode_t mode)
{
    LV_UNUSED(drv);

    String full_path = String("/") + String(path);
    Serial.println("[LVGL FS] Trying to open " + full_path);
    File *file = new File(SD.open(full_path.c_str(), FILE_READ));
    if (!file || !file->available()) {
        Serial.println("[LVGL FS] Failed to open file: " + full_path);
        delete file;
        return NULL;
    }

    lvgl_file_t * file_wrapper = (lvgl_file_t *)malloc(sizeof(lvgl_file_t));
    if (!file_wrapper) {
        Serial.println("[LVGL FS] Failed to allocate memory for file wrapper.");
        file->close();
        delete file;
        return NULL;
    }

    file_wrapper->file = file;
    return file_wrapper;
}

lv_fs_res_t StorageMgr::LVGL_SD_READ_CALLBACK(lv_fs_drv_t * drv, void * file_p, void * buf, uint32_t btr, uint32_t * br)
{
    LV_UNUSED(drv);

    lvgl_file_t * file_wrapper = (lvgl_file_t *)file_p;
    if (!file_wrapper || !file_wrapper->file) {
        return LV_FS_RES_UNKNOWN;
    }

    *br = file_wrapper->file->read((uint8_t *)buf, btr);
    return LV_FS_RES_OK;
}

lv_fs_res_t StorageMgr::LVGL_SD_SEEK_CALLBACK(lv_fs_drv_t * drv, void * file_p, uint32_t pos, lv_fs_whence_t whence)
{
    LV_UNUSED(drv);

    lvgl_file_t * file_wrapper = (lvgl_file_t *)file_p;
    if (!file_wrapper || !file_wrapper->file) {
        return LV_FS_RES_UNKNOWN;
    }

    bool success = file_wrapper->file->seek(pos);
    if (!success) {
        return LV_FS_RES_UNKNOWN;
    }
    return LV_FS_RES_OK;
}

lv_fs_res_t StorageMgr::LVGL_SD_CLOSE_CALLBACK(lv_fs_drv_t * drv, void * file_p)
{
    LV_UNUSED(drv);

    lvgl_file_t * file_wrapper = (lvgl_file_t *)file_p;
    if (!file_wrapper || !file_wrapper->file) {
        return LV_FS_RES_UNKNOWN;
    }

    file_wrapper->file->close();
    delete file_wrapper->file;
    free(file_wrapper); // malloc으로 만든거 free 해줘야 메모리 누수 없음
    return LV_FS_RES_OK;
}

void StorageMgr::RegisterLvglSdFs(void)
{
    if(SD.exists("/")) {
        Serial.println("[LVGL FS] SD card is mounted and exists.");
    } else {
        Serial.println("[LVGL FS] SD card does not exist or is not mounted.");
        return;
    }

    lv_fs_drv_init(&fs_drv);

    fs_drv.letter = 'S'; // 'S:'는 SD카드를 의미
    fs_drv.open_cb = LVGL_SD_OPEN_CALLBACK;
    fs_drv.read_cb = LVGL_SD_READ_CALLBACK;
    fs_drv.seek_cb = LVGL_SD_SEEK_CALLBACK;
    fs_drv.close_cb = LVGL_SD_CLOSE_CALLBACK;

    lv_fs_drv_register(&fs_drv);

    Serial.println("[LVGL FS] SD filesystem driver registered successfully.");

    lv_fs_drv_t* lv_sd_drive = lv_fs_get_drv('S');
    if(lv_sd_drive != NULL) {
        Serial.println("[LVGL FS] SD filesystem driver is available.");
    } else {
        Serial.println("[LVGL FS] SD filesystem driver is not available.");
    }

    Serial.println("[LVGL FS in Storage] 등록된 파일 시스템 드라이버 목록:");

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
        Serial.println("[LVGL FS in Storage] 등록된 드라이버가 없습니다.");
    }
    Serial.printf("[StorageMgr] Task Handle: %p\n", xTaskGetCurrentTaskHandle());
}

void StorageMgr::RegisterLvglSpiffsFs(void)
{
    if(SPIFFS.begin()) {
        Serial.println("[LVGL FS] SPIFFS initialized successfully.");
    } else {
        Serial.println("[LVGL FS] SPIFFS initialization failed!");
        return;
    }

    lv_fs_drv_init(&fs_drv);

    fs_drv.letter = 'S'; // 'S:'는 SPIFFS를 의미
    fs_drv.open_cb = LVGL_SPIFFS_OPEN_CALLBACK;
    fs_drv.read_cb = LVGL_SPIFFS_READ_CALLBACK;
    fs_drv.seek_cb = LVGL_SPIFFS_SEEK_CALLBACK;
    fs_drv.close_cb = LVGL_SPIFFS_CLOSE_CALLBACK;

    lv_fs_drv_register(&fs_drv);

    Serial.println("[LVGL FS] SPIFFS filesystem driver registered successfully.");

    lv_fs_drv_t* check_fs_drv = lv_fs_get_drv('S');
    if(check_fs_drv != NULL) {
        Serial.println("[LVGL FS] SD filesystem driver is available.");
    } else {
        Serial.println("[LVGL FS] SD filesystem driver is not available.");
    }

    Serial.println("[LVGL FS in Storage] 등록된 파일 시스템 드라이버 목록:");

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
        Serial.println("[LVGL FS in Storage] 등록된 드라이버가 없습니다.");
    }
    Serial.printf("[StorageMgr] Task Handle: %p\n", xTaskGetCurrentTaskHandle());
}

/*
void * StorageMgr::LVGL_SPIFFS_OPEN_CALLBACK(lv_fs_drv_t * drv, const char * path, lv_fs_mode_t mode)
{
    LV_UNUSED(drv); // 사용하지 않으면 매크로로 경고 없애줌

    String full_path = String("/spiffs/") + String(path); // SPIFFS의 경로는 /spiffs/부터 시작
    File file = SPIFFS.open(full_path.c_str(), FILE_READ);

    if (!file) {
        Serial.print("[LVGL FS] Failed to open file: ");
        Serial.println(full_path);
        return NULL; // 파일 열기 실패
    }

    lvgl_file_t * file_wrapper = (lvgl_file_t *)malloc(sizeof(lvgl_file_t));
    if (!file_wrapper) {
        Serial.println("[LVGL FS] Failed to allocate memory for file wrapper.");
        file.close();
        return NULL;
    }

    file_wrapper->file = file;
    return file_wrapper;
}

lv_fs_res_t StorageMgr::LVGL_SPIFFS_READ_CALLBACK(lv_fs_drv_t * drv, void * file_p, void * buf, uint32_t btr, uint32_t * br)
{
    LV_UNUSED(drv);

    lvgl_file_t * file_wrapper = (lvgl_file_t *)file_p;
    if (!file_wrapper || !file_wrapper->file) {
        return LV_FS_RES_UNKNOWN;
    }

    *br = file_wrapper->file.read((uint8_t *)buf, btr);
    return LV_FS_RES_OK;
}

lv_fs_res_t StorageMgr::LVGL_SPIFFS_SEEK_CALLBACK(lv_fs_drv_t * drv, void * file_p, uint32_t pos, lv_fs_whence_t whence)
{
    LV_UNUSED(drv);

    lvgl_file_t * file_wrapper = (lvgl_file_t *)file_p;
    if (!file_wrapper || !file_wrapper->file) {
        return LV_FS_RES_UNKNOWN;
    }

    bool success = file_wrapper->file.seek(pos);
    if (!success) {
        return LV_FS_RES_UNKNOWN;
    }
    return LV_FS_RES_OK;
}

lv_fs_res_t StorageMgr::LVGL_SPIFFS_CLOSE_CALLBACK(lv_fs_drv_t * drv, void * file_p)
{
    LV_UNUSED(drv);

    lvgl_file_t * file_wrapper = (lvgl_file_t *)file_p;
    if (!file_wrapper || !file_wrapper->file) {
        return LV_FS_RES_UNKNOWN;
    }

    file_wrapper->file.close();
    free(file_wrapper); // malloc으로 만든거 free 해줘야 메모리 누수 없음
    return LV_FS_RES_OK;
}
*/