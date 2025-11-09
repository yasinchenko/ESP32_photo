/ =========================
// /src/hw/hcsr04.h
// =========================
#pragma once
#include <Arduino.h>


class HCSR04 {
public:
HCSR04(uint8_t trig, uint8_t echo) : trig_(trig), echo_(echo) {}
void begin(){ pinMode(trig_, OUTPUT); pinMode(echo_, INPUT); digitalWrite(trig_, LOW);}
float read_cm(uint16_t attempts = 3) const; // усреднение/медиана
private:
uint8_t trig_, echo_;
};