// =========================
// /src/vision/face_detect.cpp
// =========================
#include "face_detect.h"


// Вариант A: лёгкая заглушка (по умолчанию)
#ifndef USE_ESP_FACE
bool FACE::begin(){ return true; }
bool FACE::detect(const camera_fb_t* fb){ (void)fb; return false; }
#else
// Вариант B: интеграция с ESP-WHO/esp-face (нужна сборка с соответствующими библиотеками)
#include "fd_forward.h" // примерные заголовки ESP-WHO
#include "fr_forward.h"
static mtmn_config_t mtmn_cfg;


bool FACE::begin(){
mtmn_cfg = mtmn_init_config();
return true;
}


bool FACE::detect(const camera_fb_t* fb){
if(!fb) return false;
box_array_t* boxes = face_detect(fb->buf, fb->width, fb->height, fb->format, mtmn_cfg);
bool found = boxes && boxes->len > 0;
if(boxes) free(boxes);
return found;
}
#endif