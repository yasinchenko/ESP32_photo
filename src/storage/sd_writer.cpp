// =========================
// /src/storage/sd_writer.cpp
// =========================
#include "sd_writer.h"


bool SDWR::begin(){
// SD_MMC для ESP32-CAM
if(!SD_MMC.begin("/sdcard", true)) return false; // 1bit mode (true) обычно стабильнее
return true;
}


void SDWR::end(){ SD_MMC.end(); }


String SDWR::makePath(bool people, const String& stamp){
String dir = people ? "/people" : "/analysis";
String path = dir + String("/") + stamp + String(".jpg");
// ensure dir
SD_MMC.mkdir(dir);
return path;
}


bool SDWR::saveJpeg(const uint8_t* buf, size_t len, bool toPeople, const String& stamp){
String path = makePath(toPeople, stamp);
File f = SD_MMC.open(path, FILE_WRITE);
if(!f) return false;
size_t w = f.write(buf, len);
f.close();
return (w==len);
}