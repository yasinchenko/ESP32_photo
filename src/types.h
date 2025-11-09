// =========================
// /src/types.h
// =========================
#pragma once
#include <Arduino.h>


enum class MotionMode : uint8_t {
STOP = 0,
FWD,
BACK,
TURN_LEFT,
TURN_RIGHT
};


enum class State : uint8_t {
BOOT = 0,
SCAN_BEFORE_MOVE,
RANGE_AND_PLAN,
MOVE_SEGMENT,
SCAN_AFTER_MOVE,
ANTI_SLIP,
PHOTO
};


struct Ranges {
float dF_cm = NAN; // front
float dR_cm = NAN; // right
uint32_t ts_ms = 0;
};