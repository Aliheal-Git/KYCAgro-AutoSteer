/*
 * app.cpp
 *
 *  Created on: Aug 24, 2025
 *      Author: alica
 */
#include "app.h"

#include "Page.hpp"
#include "cmsis_os.h"
#include "gpio.h"
#include "tim.h"
#include "main.h"

#include "Window.hpp"
#include "Flowmeter.hpp"
#include "Controller.hpp"
#include "micros.h"
#include "Valve.hpp"
#include "Settings.hpp"

#include "Button.h"

volatile uint32_t overFlowCounter = 0;

Flowmeter flowmeter(637);
Controller controller;
Settings settings;
	
ProportionalValve propValve(&htim1, TIM_CHANNEL_1, &htim1, TIM_CHANNEL_2);
Valve mainValve(VALF8_ON_GPIO_Port, VALF8_ON_Pin, VALF8_OFF_GPIO_Port, VALF8_OFF_Pin);
Valve Valves[5] = {
	Valve(VALF1_ON_GPIO_Port, VALF1_ON_Pin, VALF1_OFF_GPIO_Port, VALF1_OFF_Pin),
	Valve(VALF2_ON_GPIO_Port, VALF2_ON_Pin, VALF2_OFF_GPIO_Port, VALF2_OFF_Pin),
	Valve(VALF3_ON_GPIO_Port, VALF3_ON_Pin, VALF3_OFF_GPIO_Port, VALF3_OFF_Pin),
	Valve(VALF4_ON_GPIO_Port, VALF4_ON_Pin, VALF4_OFF_GPIO_Port, VALF4_OFF_Pin),
	Valve(VALF5_ON_GPIO_Port, VALF5_ON_Pin, VALF5_OFF_GPIO_Port, VALF5_OFF_Pin)
};

Window mainWindow;
std::unique_ptr<WelcomePage> welcomePage;
std::unique_ptr<MainPage> mainPage;
std::unique_ptr<SettingsPage> settingsPage;
std::unique_ptr<ProgramsPage> programsPage;
std::unique_ptr<InformationPage> informationPage;

void app_init(){
	startMicros();
	HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_2);
	HAL_TIM_Base_Start_IT(&htim3);

	settings.disableWPFlash();
	settings.readSettingsFlash();
	
	controller.setTargetDosage(0);

	controller.init();
	propValve.init();


	mainWindow.initiliaze();
	welcomePage = std::make_unique<WelcomePage>(&mainWindow);
	mainPage = std::make_unique<MainPage>(&mainWindow);
	settingsPage = std::make_unique<SettingsPage>(&mainWindow);
	programsPage = std::make_unique<ProgramsPage>(&mainWindow);
	informationPage = std::make_unique<InformationPage>(&mainWindow);
	mainWindow.addPage(std::move(welcomePage));
	mainWindow.addPage(std::move(mainPage));
	mainWindow.addPage(std::move(settingsPage));
	mainWindow.addPage(std::move(programsPage));
	mainWindow.addPage(std::move(informationPage));
	mainWindow.showPage(0);
	xTaskNotifyGive(*mainWindow.getTaskHandle());
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim){
    if (htim->Instance == TIM3 && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2) {
    	temp_counter++;
    	if (temp_counter == 10){
    		flowmeter.calculateFrequency(HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2));
    		temp_counter = 0;
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
	  flowmeter.increaseOverFlow();
  }
}
