// =========================
// /src/utils/logger.h
// =========================
#pragma once
#include <Arduino.h>


namespace LOG {
inline void info(const char* m){ Serial.printf("[I] %s\n", m);}
inline void warn(const char* m){ Serial.printf("[W] %s\n", m);}
inline void err (const char* m){ Serial.printf("[E] %s\n", m);}
template<typename... A>
inline void printf(const char* fmt, A... a){ Serial.printf(fmt, a...); }
}