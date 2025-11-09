// =========================
// /src/storage/sd_writer.h
// =========================
#pragma once
#include <Arduino.h>
#include <FS.h>
#include <SD_MMC.h>


namespace SDWR {
bool begin();
void end();
String makePath(bool people, const String& stamp);
bool saveJpeg(const uint8_t* buf, size_t len, bool toPeople, const String& stamp);
}