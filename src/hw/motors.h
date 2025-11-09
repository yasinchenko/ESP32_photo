// =========================
// /src/hw/motors.h
// =========================
#pragma once
#include <Arduino.h>
#include "types.h"


class Motors {
public:
void begin(uint8_t ml_in1, uint8_t ml_in2, uint8_t mr_in1, uint8_t mr_in2);
void setMode(MotionMode mode, uint8_t speed=160);
MotionMode mode() const { return mode_; }
private:
uint8_t L1_, L2_, R1_, R2_;
MotionMode mode_ = MotionMode::STOP;
void driveLR(int l, int r); // -255..255
};