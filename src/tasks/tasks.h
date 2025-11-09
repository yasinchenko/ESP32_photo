// =========================
// /src/tasks/tasks.h
// =========================
#pragma once
#include <Arduino.h>
#include "types.h"
#include "hw/hcsr04.h"
#include "control/motion.h"
#include "vision/frame_diff.h"
#include "vision/face_detect.h"
#include "storage/sd_writer.h"
#include "hw/led_flash.h"


struct AppCtx {
// HW
HCSR04* front=nullptr; HCSR04* right=nullptr;
MotionCtl* motion=nullptr; LedFlash* flash=nullptr;
// State
volatile State state = State::BOOT;
volatile Ranges ranges;
// Vision helpers
FrameDiff diff;
};


void taskSensors(void* arg);
void taskMotion(void* arg);
void taskVision(void* arg);