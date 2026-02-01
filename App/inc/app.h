// File: app.h
// Path: App\inc\app.h
// Created by Alican on 2026-01-31

#ifndef APP_INC_APP_H_
#define APP_INC_APP_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "tim.h"
void app_init();
void TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#ifdef __cplusplus
}
#endif

#endif // APP_INC_APP_H_