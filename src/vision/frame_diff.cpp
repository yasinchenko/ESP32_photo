// =========================
// /src/vision/frame_diff.cpp
// =========================
#include "frame_diff.h"
#include "app_config.h"
#include <esp_camera.h>


static camera_fb_t* snap(){ return esp_camera_fb_get(); }
static void release(camera_fb_t* fb){ if(fb) esp_camera_fb_return(fb); }


DiffResult FrameDiff::analyze(uint32_t dt_ms, float thresh){
DiffResult r; r.energy=0; r.motion=false;
camera_fb_t* a = snap(); if(!a) return r;
delay(dt_ms);
camera_fb_t* b = snap(); if(!b){ release(a); return r; }
// Простейшая разница по подвыборке байтов
size_t step = max<size_t>(1, a->len/2000); // 2k выборок
size_t n=0; uint32_t e=0;
for(size_t i=0; i<a->len && i<b->len; i+=step){ e += abs((int)a->buf[i] - (int)b->buf[i]); ++n; }
release(a); release(b);
if(n){ r.energy = (float)e / (float)n; r.motion = (r.energy >= thresh); }
return r;
}