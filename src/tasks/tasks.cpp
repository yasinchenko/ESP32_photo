// =========================
case State::SCAN_AFTER_MOVE:
vTaskDelay(pdMS_TO_TICKS(80));
st = State::SCAN_BEFORE_MOVE; break;


case State::ANTI_SLIP: {
C->motion->back(CFG::BACK_SPEED); vTaskDelay(pdMS_TO_TICKS(CFG::ANTISLIP_BACK_MS));
C->motion->turnL(CFG::TURN_SPEED); vTaskDelay(pdMS_TO_TICKS(CFG::ANTISLIP_TURN_MS));
C->motion->stop();
st = State::SCAN_BEFORE_MOVE; break; }


case State::PHOTO: {
// Обработка фото выполняется в taskVision; здесь только ожидание завершения и возврат
st = State::SCAN_BEFORE_MOVE; break; }
}
C->state = st;
}
}


void taskVision(void* arg){
C = (AppCtx*)arg;
for(;;){
if(C->state==State::SCAN_BEFORE_MOVE || C->state==State::SCAN_AFTER_MOVE){
// Разница кадров
auto diff = C->diff.analyze(CFG::FRAME_DIFF_DT_MS, CFG::FRAME_DIFF_THRESH);
if(diff.motion){
// Доп.проверка лиц (если подключено)
camera_fb_t* fb = esp_camera_fb_get();
bool face = false;
if(fb){ face = FACE::detect(fb); esp_camera_fb_return(fb); }
if(face){
// Переходим в фото-сценарий: стоп, вспышка, снимок, запись
C->state = State::PHOTO;
C->motion->stop();
C->flash->on(255);


// захватываем кадр для сохранения
camera_fb_t* shot = esp_camera_fb_get();
bool saved = false;
if(shot){
// без очереди, синхронная запись в этом примере
if(SDWR::begin()){
// формируем штамп
char stamp[24]; snprintf(stamp, sizeof(stamp), "%lu", (unsigned long)millis());
saved = SDWR::saveJpeg(shot->buf, shot->len, /*toPeople=*/true, String(stamp));
SDWR::end();
}
esp_camera_fb_return(shot);
}
C->flash->off();
LOG::printf("PHOTO saved=%d
", (int)saved);
C->state = State::SCAN_BEFORE_MOVE;
}
}
}
vTaskDelay(pdMS_TO_TICKS(50));
}
}