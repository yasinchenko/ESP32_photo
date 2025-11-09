// =========================
// /src/hw/hcsr04.cpp
// =========================
#include "hcsr04.h"


static float read_once_cm(uint8_t trig, uint8_t echo){
digitalWrite(trig, LOW); delayMicroseconds(2);
digitalWrite(trig, HIGH); delayMicroseconds(10);
digitalWrite(trig, LOW);
unsigned long duration = pulseIn(echo, HIGH, 30000UL); // 30ms ~ 5m
if(duration == 0) return NAN;
float distance_cm = duration * 0.0343f / 2.0f; // speed of sound ~343 m/s
return distance_cm;
}


float HCSR04::read_cm(uint16_t attempts) const {
// простая медиана для устойчивости
if(attempts < 1) attempts = 1;
float best = NAN;
for(uint16_t i=0; i<attempts; ++i){
float v = read_once_cm(trig_, echo_);
if(!isnan(v)){
if(isnan(best) || v < best) best = v; // возьмём минимальное как устойчивую оценку
}
delay(25); // анти-переотражение
}
return best;
}