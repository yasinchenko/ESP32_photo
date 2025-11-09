// =========================
// /src/control/motion.h
// =========================
#pragma once
#include <Arduino.h>
#include "types.h"
#include "hw/motors.h"


class MotionCtl {
public:
void begin(Motors* m){ m_ = m; }
void stop(){ m_->setMode(MotionMode::STOP); }
void fwd(uint8_t s){ m_->setMode(MotionMode::FWD, s); }
void back(uint8_t s){ m_->setMode(MotionMode::BACK, s); }
void turnL(uint8_t s){ m_->setMode(MotionMode::TURN_LEFT, s); }
void turnR(uint8_t s){ m_->setMode(MotionMode::TURN_RIGHT, s); }
MotionMode mode() const { return m_->mode(); }
private:
Motors* m_ = nullptr;
};