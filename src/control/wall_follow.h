// =========================
// /src/control/wall_follow.h
// =========================
#pragma once
#include <Arduino.h>
#include "app_config.h"
#include "control/motion.h"


class WallFollow {
public:
explicit WallFollow(MotionCtl* ctl): ctl_(ctl){}
void tick(float dR_cm){
float err = dR_cm - CFG::RIGHT_TARGET_CM;
if(isnan(err)) { ctl_->fwd(CFG::BASE_SPEED); return; }
// Простейший P-регулятор (можно добавить D)
float kP = 6.0f; // подберите
int bias = (int)(kP * err);
int base = CFG::BASE_SPEED;
int L = constrain(base - bias, 0, 255);
int R = constrain(base + bias, 0, 255);
// Имитация раздельного управления: переводим в поворот при сильной ошибке
if(abs(bias) > 60){ (bias>0) ? ctl_->turnR(CFG::TURN_SPEED) : ctl_->turnL(CFG::TURN_SPEED); }
else { // прямой ход с небольшим смещением
// Упрощённо: используем только базовый FWD, PWM делим поровну (моторный класс делает одинаковые колёса)
ctl_->fwd((uint8_t)((L+R)/2));
}
}
private:
MotionCtl* ctl_;
};