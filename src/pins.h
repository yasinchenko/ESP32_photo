// =========================
// /src/pins.h
// =========================
#pragma once
#include <Arduino.h>


namespace PINS {
// HC-SR04 (Front)
static constexpr uint8_t HCSR04F_ECHO = 4; // IO4
static constexpr uint8_t HCSR04F_TRIG = 2; // IO2
// HC-SR04 (Right)
static constexpr uint8_t HCSR04R_ECHO = 15; // IO15
static constexpr uint8_t HCSR04R_TRIG = 16; // IO16


// Motors (пример для драйвера HR8833; подправьте под своё подключение)
static constexpr uint8_t ML_IN1 = 13;
static constexpr uint8_t ML_IN2 = 14;
static constexpr uint8_t MR_IN1 = 3; // предупреждение: IO3 на ESP32-CAM — U0RXD; проверьте разводку
static constexpr uint8_t MR_IN2 = 1; // IO1 — U0TXD


// LED Flash
static constexpr uint8_t LED_FLASH = 12; // встроенная вспышка ESP32-CAM
}