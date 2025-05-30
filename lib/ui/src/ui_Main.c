// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.5.0
// LVGL version: 9.1.0
// Project name: pride_ui

#include "ui.h"

void ui_Main_screen_init(void)
{
    ui_Main = lv_obj_create(NULL);
    lv_obj_remove_flag(ui_Main, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Main, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Main, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Panel1 = lv_obj_create(ui_Main);
    lv_obj_set_width(ui_Panel1, 260);
    lv_obj_set_height(ui_Panel1, 48);
    lv_obj_set_x(ui_Panel1, -2);
    lv_obj_set_y(ui_Panel1, 86);
    lv_obj_set_align(ui_Panel1, LV_ALIGN_CENTER);
    lv_obj_remove_flag(ui_Panel1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Panel1, lv_color_hex(0x7D7D7D), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Panel1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Panel1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Panel1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_voltage_title = lv_label_create(ui_Main);
    lv_obj_set_width(ui_voltage_title, LV_SIZE_CONTENT);   /// 8
    lv_obj_set_height(ui_voltage_title, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_voltage_title, -23);
    lv_obj_set_y(ui_voltage_title, -90);
    lv_obj_set_align(ui_voltage_title, LV_ALIGN_CENTER);
    lv_label_set_text(ui_voltage_title, "Voltage (V)");
    lv_obj_set_style_text_color(ui_voltage_title, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_voltage_title, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_voltage_title, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_coolant_title = lv_label_create(ui_Main);
    lv_obj_set_width(ui_coolant_title, LV_SIZE_CONTENT);   /// 8
    lv_obj_set_height(ui_coolant_title, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_coolant_title, -21);
    lv_obj_set_y(ui_coolant_title, -5);
    lv_obj_set_align(ui_coolant_title, LV_ALIGN_CENTER);
    lv_label_set_text(ui_coolant_title, "Coolant (°C)");
    lv_obj_set_style_text_color(ui_coolant_title, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_coolant_title, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_coolant_title, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_cpu_usage_title = lv_label_create(ui_Main);
    lv_obj_set_width(ui_cpu_usage_title, LV_SIZE_CONTENT);   /// 8
    lv_obj_set_height(ui_cpu_usage_title, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_cpu_usage_title, 43);
    lv_obj_set_y(ui_cpu_usage_title, 78);
    lv_obj_set_align(ui_cpu_usage_title, LV_ALIGN_CENTER);
    lv_label_set_text(ui_cpu_usage_title, "CPU");
    lv_obj_set_style_text_color(ui_cpu_usage_title, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_cpu_usage_title, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_cpu_usage_title, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ram_usage_title = lv_label_create(ui_Main);
    lv_obj_set_width(ui_ram_usage_title, LV_SIZE_CONTENT);   /// 8
    lv_obj_set_height(ui_ram_usage_title, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_ram_usage_title, 43);
    lv_obj_set_y(ui_ram_usage_title, 95);
    lv_obj_set_align(ui_ram_usage_title, LV_ALIGN_CENTER);
    lv_label_set_text(ui_ram_usage_title, "RAM");
    lv_obj_set_style_text_color(ui_ram_usage_title, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_ram_usage_title, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_ram_usage_title, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ram_usage = lv_label_create(ui_Main);
    lv_obj_set_width(ui_ram_usage, LV_SIZE_CONTENT);   /// 8
    lv_obj_set_height(ui_ram_usage, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_ram_usage, 90);
    lv_obj_set_y(ui_ram_usage, 95);
    lv_obj_set_align(ui_ram_usage, LV_ALIGN_CENTER);
    lv_label_set_text(ui_ram_usage, "32%");
    lv_obj_set_style_text_color(ui_ram_usage, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_ram_usage, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_ram_usage, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_cpu_usage = lv_label_create(ui_Main);
    lv_obj_set_width(ui_cpu_usage, LV_SIZE_CONTENT);   /// 8
    lv_obj_set_height(ui_cpu_usage, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_cpu_usage, 90);
    lv_obj_set_y(ui_cpu_usage, 78);
    lv_obj_set_align(ui_cpu_usage, LV_ALIGN_CENTER);
    lv_label_set_text(ui_cpu_usage, "32%");
    lv_obj_set_style_text_color(ui_cpu_usage, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_cpu_usage, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_cpu_usage, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_obd_status = lv_label_create(ui_Main);
    lv_obj_set_width(ui_obd_status, LV_SIZE_CONTENT);   /// 8
    lv_obj_set_height(ui_obd_status, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_obd_status, -54);
    lv_obj_set_y(ui_obd_status, 87);
    lv_obj_set_align(ui_obd_status, LV_ALIGN_CENTER);
    lv_label_set_text(ui_obd_status, "OBD Connected");
    lv_obj_set_style_text_color(ui_obd_status, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_obd_status, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_obd_status, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Image1 = lv_image_create(ui_Main);
    lv_image_set_src(ui_Image1, &ui_img_427324742);
    lv_obj_set_width(ui_Image1, LV_SIZE_CONTENT);   /// 40
    lv_obj_set_height(ui_Image1, LV_SIZE_CONTENT);    /// 36
    lv_obj_set_x(ui_Image1, -108);
    lv_obj_set_y(ui_Image1, -6);
    lv_obj_set_align(ui_Image1, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image1, LV_OBJ_FLAG_CLICKABLE);     /// Flags
    lv_obj_remove_flag(ui_Image1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Image4 = lv_image_create(ui_Main);
    lv_image_set_src(ui_Image4, &ui_img_1638550806);
    lv_obj_set_width(ui_Image4, LV_SIZE_CONTENT);   /// 40
    lv_obj_set_height(ui_Image4, LV_SIZE_CONTENT);    /// 34
    lv_obj_set_x(ui_Image4, -109);
    lv_obj_set_y(ui_Image4, -90);
    lv_obj_set_align(ui_Image4, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image4, LV_OBJ_FLAG_CLICKABLE);     /// Flags
    lv_obj_remove_flag(ui_Image4, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_bar_voltage = lv_bar_create(ui_Main);
    lv_bar_set_range(ui_bar_voltage, 0, 18);
    lv_bar_set_value(ui_bar_voltage, 0, LV_ANIM_ON);
    lv_bar_set_start_value(ui_bar_voltage, 0, LV_ANIM_OFF);
    lv_obj_set_width(ui_bar_voltage, 257);
    lv_obj_set_height(ui_bar_voltage, 10);
    lv_obj_set_x(ui_bar_voltage, -3);
    lv_obj_set_y(ui_bar_voltage, -43);
    lv_obj_set_align(ui_bar_voltage, LV_ALIGN_CENTER);
    lv_obj_set_style_radius(ui_bar_voltage, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_bar_voltage, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_bar_voltage, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_src(ui_bar_voltage, &ui_img_716095653, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_radius(ui_bar_voltage, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_bar_voltage, lv_color_hex(0xECF100), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_bar_voltage, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_bar_voltage, lv_color_hex(0x007507), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_bar_voltage, LV_GRAD_DIR_HOR, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    //Compensating for LVGL9.1 draw crash with bar/slider max value when top-padding is nonzero and right-padding is 0
    if(lv_obj_get_style_pad_top(ui_bar_voltage, LV_PART_MAIN) > 0) lv_obj_set_style_pad_right(ui_bar_voltage,
                                                                                           lv_obj_get_style_pad_right(ui_bar_voltage, LV_PART_MAIN) + 1, LV_PART_MAIN);
    ui_bar_coolant = lv_bar_create(ui_Main);
    lv_bar_set_range(ui_bar_coolant, 0, 150);
    lv_bar_set_value(ui_bar_coolant, 0, LV_ANIM_ON);
    lv_bar_set_start_value(ui_bar_coolant, 0, LV_ANIM_OFF);
    lv_obj_set_width(ui_bar_coolant, 257);
    lv_obj_set_height(ui_bar_coolant, 10);
    lv_obj_set_x(ui_bar_coolant, -3);
    lv_obj_set_y(ui_bar_coolant, 39);
    lv_obj_set_align(ui_bar_coolant, LV_ALIGN_CENTER);
    lv_obj_set_style_radius(ui_bar_coolant, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_bar_coolant, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_bar_coolant, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_src(ui_bar_coolant, &ui_img_716095653, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_radius(ui_bar_coolant, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_bar_coolant, lv_color_hex(0x1C6DFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_bar_coolant, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_bar_coolant, lv_color_hex(0xFF0000), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_bar_coolant, LV_GRAD_DIR_HOR, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    //Compensating for LVGL9.1 draw crash with bar/slider max value when top-padding is nonzero and right-padding is 0
    if(lv_obj_get_style_pad_top(ui_bar_coolant, LV_PART_MAIN) > 0) lv_obj_set_style_pad_right(ui_bar_coolant,
                                                                                           lv_obj_get_style_pad_right(ui_bar_coolant, LV_PART_MAIN) + 1, LV_PART_MAIN);
    ui_Label1 = lv_label_create(ui_Main);
    lv_obj_set_width(ui_Label1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label1, 122);
    lv_obj_set_y(ui_Label1, 23);
    lv_obj_set_align(ui_Label1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label1, "150");
    lv_obj_set_style_text_color(ui_Label1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label1, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label2 = lv_label_create(ui_Main);
    lv_obj_set_width(ui_Label2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label2, -130);
    lv_obj_set_y(ui_Label2, 25);
    lv_obj_set_align(ui_Label2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label2, "0");
    lv_obj_set_style_text_color(ui_Label2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label2, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label3 = lv_label_create(ui_Main);
    lv_obj_set_width(ui_Label3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label3, -4);
    lv_obj_set_y(ui_Label3, 24);
    lv_obj_set_align(ui_Label3, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label3, "75");
    lv_obj_set_style_text_color(ui_Label3, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label3, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label4 = lv_label_create(ui_Main);
    lv_obj_set_width(ui_Label4, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label4, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label4, -130);
    lv_obj_set_y(ui_Label4, -59);
    lv_obj_set_align(ui_Label4, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label4, "6");
    lv_obj_set_style_text_color(ui_Label4, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label4, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label5 = lv_label_create(ui_Main);
    lv_obj_set_width(ui_Label5, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label5, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label5, -4);
    lv_obj_set_y(ui_Label5, -60);
    lv_obj_set_align(ui_Label5, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label5, "12");
    lv_obj_set_style_text_color(ui_Label5, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label5, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label6 = lv_label_create(ui_Main);
    lv_obj_set_width(ui_Label6, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label6, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label6, 122);
    lv_obj_set_y(ui_Label6, -61);
    lv_obj_set_align(ui_Label6, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label6, "18");
    lv_obj_set_style_text_color(ui_Label6, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label6, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label6, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);


}
