// =========================
// /src/vision/frame_diff.h
// =========================
#pragma once
#include <Arduino.h>


struct DiffResult { float energy=0; bool motion=false; };


class FrameDiff {
public:
DiffResult analyze(uint32_t dt_ms, float thresh);
};