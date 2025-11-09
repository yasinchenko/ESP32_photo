// =========================
// /src/tasks/storage.h
// =========================
#pragma once
#include <Arduino.h>
#include <esp_camera.h>
#include "storage/sd_writer.h"


struct PhotoJob {
bool toPeople = true;
String stamp;
uint8_t* buf = nullptr;
size_t len = 0;
};


void taskStorage(void* arg);
bool enqueuePhoto(const uint8_t* data, size_t len, bool toPeople, const String& stamp);