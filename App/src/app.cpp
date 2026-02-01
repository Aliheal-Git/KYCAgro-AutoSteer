#include "app.h"
#include "tim.h"
#include "main.h"

#include "Flowmeter.hpp"
#include "GPS.hpp"
#include "Flash.hpp"
#include "Valve.hpp"
#include "Window.hpp"
#include "Button.h"

#include "ButtonService.hpp"

#include "ValveController.hpp"
#include "DosageController.hpp"


volatile uint8_t flowmeterPulseCounter = 0;

using namespace App::Drivers;
using namespace App::Services;
namespace App {
	//Services
	ButtonService buttonService;

	// Drivers
	Flowmeter flowmeter(450, 20000.0f, 0.1f, 0.01f, 1.0f, 0.01f);
	GPS gps;
	Window window(&hi2c1, 0x27 << 1, 2, 16);
	Flash flash;

	// Buttons
	// To act like switch increase limit of pressDurationMs
	Button* buttons[MAX_BUTTON] = {
		new Button(ButtonType::MAIN, 0xFFFFFFFFFFFF, 0, false, BUTTON_MAIN_GPIO_Port, BUTTON_MAIN_Pin, buttonService),
		new Button(ButtonType::GPS, 0xFFFFFFFFFFFF, 0, false, BUTTON_GPS_GPIO_Port, BUTTON_GPS_Pin, buttonService),
		new Button(ButtonType::DOSAGE, 0xFFFFFFFFFFFF, 0, false, BUTTON_MODE_GPIO_Port, BUTTON_MODE_Pin, buttonService),
		new Button(ButtonType::PLUS, 1500, 300, false, BUTTON_PLUS_GPIO_Port, BUTTON_PLUS_Pin, buttonService),
		new Button(ButtonType::MINUS, 1500, 300, false, BUTTON_MINUS_GPIO_Port, BUTTON_MINUS_Pin, buttonService),
		new Button(ButtonType::MENU, 2500, 0, false, BUTTON_MENU_GPIO_Port, BUTTON_MENU_Pin, buttonService),
		new Button(ButtonType::PROGRAM, 2500, 0, false, BUTTON_PROGRAM_GPIO_Port, BUTTON_PROGRAM_Pin, buttonService),
		new Button(ButtonType::VALVE1, 0xFFFFFFFFFFFF, 0, true, BUTTON_1_GPIO_Port, BUTTON_1_Pin, buttonService),
		new Button(ButtonType::VALVE2, 0xFFFFFFFFFFFF, 0, true, BUTTON_2_GPIO_Port, BUTTON_2_Pin, buttonService),
		new Button(ButtonType::VALVE3, 0xFFFFFFFFFFFF, 0, true, BUTTON_3_GPIO_Port, BUTTON_3_Pin, buttonService),
		new Button(ButtonType::VALVE4, 0xFFFFFFFFFFFF, 0, true, BUTTON_4_GPIO_Port, BUTTON_4_Pin, buttonService),
		new Button(ButtonType::VALVE5, 0xFFFFFFFFFFFF, 0, true, BUTTON_5_GPIO_Port, BUTTON_5_Pin, buttonService),
		new Button(ButtonType::VALVE6, 0xFFFFFFFFFFFF, 0, true, BUTTON_6_GPIO_Port, BUTTON_6_Pin, buttonService),
		new Button(ButtonType::VALVE7, 0xFFFFFFFFFFFF, 0, true, BUTTON_7_GPIO_Port, BUTTON_7_Pin, buttonService),
		new Button(ButtonType::VALVE8, 0xFFFFFFFFFFFF, 0, true, BUTTON_8_GPIO_Port, BUTTON_8_Pin, buttonService),
		nullptr
	};

	//Valves
	Valve* mainValve = new Valve(VALF9_ON_GPIO_Port, VALF9_ON_Pin, VALF10_OFF_PWM_GPIO_Port, VALF10_OFF_PWM_Pin);
	ProportionalValve* proportionalValve = new ProportionalValve(&htim1, TIM_CHANNEL_1, &htim1, TIM_CHANNEL_2);	
	Valve* nozzleValves[MAX_NOZZLE_VALVES] = {
		new Valve(VALF1_ON_GPIO_Port, VALF1_ON_Pin, VALF1_OFF_GPIO_Port, VALF1_OFF_Pin),
		new Valve(VALF2_ON_GPIO_Port, VALF2_ON_Pin, VALF2_OFF_GPIO_Port, VALF2_OFF_Pin),
		new Valve(VALF3_ON_GPIO_Port, VALF3_ON_Pin, VALF3_OFF_GPIO_Port, VALF3_OFF_Pin),
		new Valve(VALF4_ON_GPIO_Port, VALF4_ON_Pin, VALF4_OFF_GPIO_Port, VALF4_OFF_Pin),
		new Valve(VALF5_ON_GPIO_Port, VALF5_ON_Pin, VALF5_OFF_GPIO_Port, VALF5_OFF_Pin),
		new Valve(VALF6_ON_GPIO_Port, VALF6_ON_Pin, VALF6_OFF_GPIO_Port, VALF6_OFF_Pin),
		new Valve(VALF7_ON_GPIO_Port, VALF7_ON_Pin, VALF7_OFF_GPIO_Port, VALF7_OFF_Pin),
		new Valve(VALF8_ON_GPIO_Port, VALF8_ON_Pin, VALF8_OFF_GPIO_Port, VALF8_OFF_Pin),
	};
	



	void app_init(){
		HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_2);
		HAL_TIM_Base_Start_IT(&htim3);

		// Register buttons
		for (auto* b : buttons){
			if (b != nullptr)
				buttonService.registerButton(b);
		}
	}


}

// C linkage for HAL callbacks

void app_init(){
	App::app_init();
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
