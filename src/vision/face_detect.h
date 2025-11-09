// =========================
// /src/vision/face_detect.h
// =========================
#pragma once
#include <Arduino.h>
#include <esp_camera.h>


namespace FACE {
bool begin();
bool detect(const camera_fb_t* fb); // true если найдено лицо
}