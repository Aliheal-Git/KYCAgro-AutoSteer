#include "app.h"
#include "tim.h"

#include "Flowmeter.hpp"
#include "Button.h"
#include "ButtonService.hpp"

volatile uint8_t flowmeterPulseCounter = 0;
namespace App {
	Drivers::Flowmeter flowmeter(450, 20000.0f, 0.1f, 0.01f, 1.0f, 0.01f);
	

	// Buttons
	Services::ButtonService buttonService;
	Drivers::Button mainButton(MAIN, 0xFFFFFFFFFFFF, 0, false, BUTTON_MAIN_GPIO_Port, BUTTON_MAIN_Pin, &buttonService);
}


void app_init(){
	HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_2);
	HAL_TIM_Base_Start_IT(&htim3);
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim){
    if (htim->Instance == TIM3 && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2) {
    	flowmeterPulseCounter++;
    	if (flowmeterPulseCounter >= PUSLECOUNTPERDURATION){
    		App::flowmeter.calculateFrequency(HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2));
    		flowmeterPulseCounter = 0;
    	}
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM7)
  {
    HAL_IncTick();
  }
  if (htim->Instance == TIM3){
	  App::flowmeter.onTimerOverflow();
  }
}
