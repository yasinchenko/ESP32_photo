// =========================
// /src/tasks/storage.cpp
// =========================
#include "storage.h"
#include "utils/logger.h"


static QueueHandle_t qPhotos = nullptr;


bool enqueuePhoto(const uint8_t* data, size_t len, bool toPeople, const String& stamp){
if(!qPhotos) return false;
PhotoJob job; job.toPeople=toPeople; job.stamp=stamp; job.len=len; job.buf=(uint8_t*)malloc(len);
if(!job.buf) return false;
memcpy(job.buf, data, len);
if(xQueueSend(qPhotos, &job, 0) != pdTRUE){ free(job.buf); return false; }
return true;
}


void taskStorage(void* arg){
(void)arg;
qPhotos = xQueueCreate(3, sizeof(PhotoJob));
PhotoJob job;
for(;;){
if(xQueueReceive(qPhotos, &job, portMAX_DELAY)==pdTRUE){
bool ok=false;
if(SDWR::begin()){
ok = SDWR::saveJpeg(job.buf, job.len, job.toPeople, job.stamp);
SDWR::end();
}
LOG::printf("SD save %s (%u bytes) ok=%d
", job.stamp.c_str(), (unsigned)job.len, (int)ok);
free(job.buf);
}
}
}