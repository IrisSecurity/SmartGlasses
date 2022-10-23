//=====================================================
//  THIS FILE TO BE USED FOR INTERFACING WITH DISPLAY
//=====================================================

//#pragma once
using namespace std;
#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "sdkconfig.h"
#include <iostream>
#include <driver/i2c.h>
#include <iomanip>
#include "esp_log.h"
#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"

#define LGFX_USE_V1
#define LGFX_CVBS
#define LGFX_ESP_WROVER_KIT

#include <LovyanGFX.hpp>
#include "user_setting.hpp"
#include "helper_display.hpp"
#include <gui/ui.h>

#define LOVYAN_USE_CORE_NUM 1
static const char *TAG = "lvgl_gui";

#define ENABLE_TEST_TIMER   // Enable/Disable TIMER used for auto-shutoff
#ifdef ENABLE_TEST_TIMER
    static void once_timer_callback(void* arg);
#endif

// Set everything up
void displayStart(){
    lcd.init();        // Initialize LovyanGFX
    
    lv_init();         // Initialize lvgl

    if (lv_display_init() != ESP_OK) // Configure LVGL
    {
        ESP_LOGE(TAG, "LVGL setup failed!!!");
    }

    cout << "Free heap: ";
    cout << heap_caps_get_free_size(MALLOC_CAP_8BIT) << endl;
    
    // Function generated by squareline studio to register all its ui components
    ui_init_custom();
}

//Wipe everything from screen
void displayClear(){
    lvgl_acquire();
    lv_refr_now(lv_disp_get_default());
    lvgl_release(); 
}

// To be called when the wake word is detected (or maybe on button press) 
void displayEnterVoiceCommandStep1(){
    lvgl_acquire();
    lv_scr_load(ui_Enter_Voice_Command);
    lvgl_release();

    
    cout << "Free heap AFTER VOICECMD1: ";
    cout << heap_caps_get_free_size(MALLOC_CAP_8BIT) << endl;
 
}

void displayEnterVoiceCommandStep2(){
    lvgl_acquire();
    lv_scr_load(ui_Enter_Voice_Command_2);
    lvgl_release();
}

//TODO: implement this in a decent way
void displayEnterVoiceCommandStep3(char* command, char* soFar){
    lvgl_acquire();
    lv_scr_load(ui_Enter_Voice_Command_3);
    lvgl_release();
}

void displayCardSearchTextonlyDemo(){
 lvgl_acquire();
 lv_scr_load(ui_Card_Search_Textonly);
 lvgl_release();
}