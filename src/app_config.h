// =========================
// /src/app_config.h
// =========================
#pragma once
#include <Arduino.h>


namespace CFG {
// Дистанции (см)
static constexpr float FRONT_STOP_CM = 30.0f;
static constexpr float RIGHT_TARGET_CM = 21.0f;
static constexpr float RIGHT_DEADBAND_CM = 2.5f;


// Скорости/тайминги
static constexpr uint8_t BASE_SPEED = 170; // 0..255 PWM
static constexpr uint8_t TURN_SPEED = 160;
static constexpr uint8_t BACK_SPEED = 160;
static constexpr uint32_t MOVE_SEG_MS = 500; // длительность сегмента прямого хода


// Антибукс
static constexpr uint32_t ANTISLIP_WINDOW_MS = 600; // окно измерения «прогресса»
static constexpr float ANTISLIP_EPS_CM = 1.5f; // «почти нет изменений»
static constexpr uint32_t ANTISLIP_BACK_MS = 350;
static constexpr uint32_t ANTISLIP_TURN_MS = 420;


// Визия
static constexpr uint32_t FRAME_DIFF_DT_MS = 150;
static constexpr float FRAME_DIFF_THRESH = 18.0f; // эмпирический порог


// Камера/SD
static constexpr bool SAVE_ANALYSIS_FRAMES = false; // кадры анализа в /analysis
}