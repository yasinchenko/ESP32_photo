// =========================
// /src/hw/motors.cpp
// =========================
#include "motors.h"


void Motors::begin(uint8_t ml_in1, uint8_t ml_in2, uint8_t mr_in1, uint8_t mr_in2){
L1_=ml_in1; L2_=ml_in2; R1_=mr_in1; R2_=mr_in2;
pinMode(L1_, OUTPUT); pinMode(L2_, OUTPUT);
pinMode(R1_, OUTPUT); pinMode(R2_, OUTPUT);
driveLR(0,0);
}


void Motors::driveLR(int l, int r){
l = constrain(l, -255, 255);
r = constrain(r, -255, 255);
// Простой двутакт через PWM; замените на ledcWrite при необходимости
if(l>=0){ analogWrite(L1_, l); analogWrite(L2_, 0); } else { analogWrite(L1_, 0); analogWrite(L2_, -l); }
if(r>=0){ analogWrite(R1_, r); analogWrite(R2_, 0); } else { analogWrite(R1_, 0); analogWrite(R2_, -r); }
}


void Motors::setMode(MotionMode m, uint8_t s){
mode_ = m;
switch(m){
case MotionMode::STOP: driveLR(0,0); break;
case MotionMode::FWD: driveLR(s, s); break;
case MotionMode::BACK: driveLR(-s,-s); break;
case MotionMode::TURN_LEFT: driveLR(-s, s); break;
case MotionMode::TURN_RIGHT:driveLR( s,-s); break;
}
}