// =========================
// /src/main.cpp
// =========================
#include <Arduino.h>
#include <esp_camera.h>
#include "pins.h"
#include "app_config.h"
#include "types.h"
#include "utils/logger.h"
#include "hw/hcsr04.h"
#include "hw/motors.h"
#include "hw/led_flash.h"
#include "control/motion.h"
#include "tasks/tasks.h"


static HCSR04 front(PINS::HCSR04F_TRIG, PINS::HCSR04F_ECHO);
static HCSR04 right (PINS::HCSR04R_TRIG, PINS::HCSR04R_ECHO);
static Motors motors;
static LedFlash flash(PINS::LED_FLASH);
static MotionCtl motion;
static AppCtx ctx;


static void camera_init_basic(){
camera_config_t config = {};
config.ledc_channel = LEDC_CHANNEL_0;
config.ledc_timer = LEDC_TIMER_0;
config.pin_d0 = 5; config.pin_d1 = 18; config.pin_d2 = 19; config.pin_d3 = 21;
config.pin_d4 = 36; config.pin_d5 = 39; config.pin_d6 = 34; config.pin_d7 = 35;
config.pin_xclk = 0; config.pin_pclk = 22; config.pin_vsync = 25; config.pin_href = 23;
config.pin_sccb_sda = 26; config.pin_sccb_scl = 27; config.pin_pwdn = 32; config.pin_reset = -1;
config.xclk_freq_hz = 20000000; config.pixel_format = PIXFORMAT_JPEG;
if(psramFound()){ config.frame_size = FRAMESIZE_SVGA; config.jpeg_quality = 12; config.fb_count = 2; }
else { config.frame_size = FRAMESIZE_VGA; config.jpeg_quality = 15; config.fb_count = 1; }
esp_err_t err = esp_camera_init(&config);
if(err != ESP_OK){ LOG::err("Camera init failed"); } else { LOG::info("Camera OK"); }
}


void setup(){
Serial.begin(115200); delay(200);
LOG::info("Boot");


front.begin(); right.begin();


motors.begin(PINS::ML_IN1, PINS::ML_IN2, PINS::MR_IN1, PINS::MR_IN2);
motion.begin(&motors);
flash.begin();


camera_init_basic();


ctx.front=&front; ctx.right=&right; ctx.motion=&motion; ctx.flash=&flash; ctx.state=State::BOOT;


// FreeRTOS задачи
xTaskCreatePinnedToCore(taskSensors, "sensors", 4096, &ctx, 1, nullptr, 1);
xTaskCreatePinnedToCore(taskMotion , "motion", 4096, &ctx, 1, nullptr, 1);
xTaskCreatePinnedToCore(taskVision , "vision", 6144, &ctx, 1, nullptr, 0);
}


void loop(){
// пусто — вся логика в задачах
static uint32_t last=0; if(millis()-last>1000){ last=millis();
auto r=ctx.ranges; Serial.printf("dF=%.1f dR=%.1f state=%d
", r.dF_cm, r.dR_cm, (int)ctx.state);
}
delay(10);
}