/*
 * Controller.cpp
 *
 *  Created on: Sep 2, 2025
 *      Author: alica
 */

#include "Controller.hpp"

#include "Flowmeter.hpp"
#include "OneButtonC.h"
#include "Settings.hpp"
#include "PID.h"
#include "Valve.hpp"
#include "ButtonsGlobal.h"

#include "Controller.hpp"
#include "Math.h"


uint32_t clasttime = 0;
uint32_t cinterval = 0;

Controller::Controller() : pidController(0.5, 0.008, 15,
        []() { return controller.getDosage(); },
        [](float output) {
        		propValve.setDutyCycle(output); }) {
    _currentDosage = 0.0f;
    _targetDosage = 0.0f;

    taskHandle = nullptr;
}

void Controller::init() {
    // Create the task with 'this' as the parameter
    xTaskCreate(taskEntryPoint, "Controller Task", 128*5, this, osPriority::osPriorityRealtime-1, &taskHandle);
    xTaskCreate(pidTaskEntryPoint, "PID Task", 128*5, this, osPriority::osPriorityRealtime, &taskHandle);


    pidController.setEnabled(false);
    pidController.setOutputBounds(-1.0f, 1.0f); // Assuming duty cycle is between 0% and 100%
    pidController.registerTimeFunction(HAL_GetTick);
    pidController.setMaxIntegralCumulation(50);
}

void Controller::task(){
    CANSPI_Initialize();
    for(;;){
        if(CANSPI_Receive(&rxMessage)){
            switch (rxMessage.frame.id){
                default:
                    break;
                case (VALVE_ID):
                    if(rxMessage.frame.dlc == 0x08)
                    {
                        uint16_t valve_temp = 0;
                        valve_temp = (uint16_t)rxMessage.frame.data6<<8;
                        valve_temp |= rxMessage.frame.data7;
                        uint8_t openValveCount = 0;
                        for (uint8_t i = 0;  i < maxValve; i++)
                        {
                            if (valve_temp&(1<<i)){
                                Valves[(maxValve - 1) - i].open(Valve::AUTO);
                                openValveCount++;
                            }
                            else
                                Valves[(maxValve - 1) - i].close(Valve::AUTO);
                        }
                        if (openValveCount == 0)
                            mainValve.close(Valve::AUTO);
                        else if (buttons.BUTTON_MAIN._button.state == OCS_DOWN)
                            mainValve.open(Valve::AUTO);
                    }
                    break;
                case (SPEED_ID):
                    if (settings.getSpeedSource() == Settings::GPS){
                        uint16_t temp = 0;
                        temp = (uint16_t)rxMessage.frame.data0<<8;
                        temp |= rxMessage.frame.data1;
                        temp -= (++temp)%10;
                        _speed = temp / 100.0f;
                    }
                    break;
            }
        }
        if (settings.getSpeedSource() == Settings::SIMULATION)
            _speed = settings.getSimulationSpeed();
        if (mainValve.getStatus() == Valve::Status::OPEN && settings.getMinDosage() != 0 && settings.getMaxDosage() != 0) {
            if (flowmeter.getFlowRate() < settings.getMinDosage() || flowmeter.getFlowRate() > settings.getMinDosage())
                HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_RESET);
            else
                HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_RESET);
        }
        else
            HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_RESET);
        osDelay(100);
    }
}

void Controller::pidTask(){
	osDelay(5000);
	propValve.setDutyCycle(-1);
	controller.setTargetDosage(settings.getDosageValue(settings.getSelectedProgram()));
	for(;;){
	    calculateDosage();

	    if (flowmeter.checkNoFlow() && (mainValve.getStatus() == Valve::OPEN)){
		    pidController.tick();
	    }
	    else if (controller._mode == Controller::Mode::AUTO && mainValve.getStatus() == Valve::OPEN) {
	    	propValve.setDutyCycle(-1);
	    }
	    else if (controller._mode == Controller::Mode::AUTO) {
	    	propValve.setDutyCycle(0);
	    }
	    if (!flowmeter.checkNoFlow()){
	    	_currentDosage = 0.0f;
	    }
	    clasttime = xTaskGetTickCount();
	    osDelay(10);
	    cinterval = xTaskGetTickCount() - clasttime;
	    UNUSED(cinterval);
	}
}

void Controller::enablePIDController() {
    pidController.setEnabled(true);
}

void Controller::disablePIDController() {
    pidController.setEnabled(false);
    propValve.setDutyCycle(0.0f); // Ensure valve is closed when PID is disabled
}

void Controller::setTargetDosage(float dosage) {
	if (dosage > (settings.getDosageValue(settings.getSelectedProgram()) + settings.getMaxDosageVariationPercent()/100.0f*settings.getDosageValue(settings.getSelectedProgram())))
		_targetDosage = settings.getDosageValue(settings.getSelectedProgram()) + settings.getMaxDosageVariationPercent()/100.0f*settings.getDosageValue(settings.getSelectedProgram());
	else 
    if (dosage < (settings.getDosageValue(settings.getSelectedProgram()) - settings.getMaxDosageVariationPercent()/100.0f*settings.getDosageValue(settings.getSelectedProgram())))
		_targetDosage = settings.getDosageValue(settings.getSelectedProgram()) - settings.getMaxDosageVariationPercent()/100.0f*settings.getDosageValue(settings.getSelectedProgram());
    else
	    _targetDosage = dosage;
    pidController.setTarget(dosage);
}

void Controller::calculateDosage(){
    double temp = 0;
    if (settings.getNozzleCount() > 0 && settings.getNozzleDistance() > 0)
        temp = 60*flowmeter.getFlowRate()/settings.getNozzleCount()/settings.getNozzleDistance()*100.0f;
    if (settings.getSpeedSource() == Settings::SIMULATION)
        _currentDosage = temp / settings.getSimulationSpeed();
    else
        _currentDosage = temp / controller.getSpeed();
}

void Controller::setSpeed(const float speed){
    _speed = speed;
}

void Controller::setMode(Mode m) {
    _mode = m;
    if (m == MANUAL) {
        disablePIDController();
    } else {
        enablePIDController();
    }
}

Controller::Mode Controller::getMode() const {
    return _mode;
}
