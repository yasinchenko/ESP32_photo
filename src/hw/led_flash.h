// =========================
// /src/hw/led_flash.h
// =========================
#pragma once
#include <Arduino.h>


class LedFlash {
public:
explicit LedFlash(uint8_t pin): pin_(pin){}
void begin(){ pinMode(pin_, OUTPUT); off(); }
void on(uint8_t pwm=255){ analogWrite(pin_, pwm); }
void off(){ analogWrite(pin_, 0); }
private:
uint8_t pin_;
};