/*
 * Controller.cpp
 *
 *  Created on: Sep 2, 2025
 *      Author: alica
 */

#include "PID.h"
#include "DosageController.hpp"
#include "Math.h"
#include "SettingsCommon.hpp"
#include "stm32g0xx_hal.h"

using namespace App::Controller::DosageController;

uint32_t clasttime = 0;
uint32_t cinterval = 0;

DosageController::DosageController(float P, float I, float D, Settings* Settings, IGPS* gpsDevice, IFlowmeter* flowmeterDevice, IValve* propValveDevice) :
                pidController(P, I, D, nullptr, nullptr),
                settings(Settings), 
                gps(gpsDevice),
                flowmeter(flowmeterDevice),
                proportionalValve(propValveDevice){
    
}

void DosageController::init() {
    pidController.setPIDSource([this]() { return this->calculateDosage(); });
    pidController.setPIDOutput([this](float output) {
        this->proportionalValve->setDutyCycle(output);
    });
    pidController.setEnabled(false);
    pidController.setOutputBounds(-1.0f, 1.0f); // Assuming duty cycle is between 0% and 100%
    pidController.registerTimeFunction(HAL_GetTick);
    pidController.setMaxIntegralCumulation(50);
}


DosageControllerTaskResult DosageController::tick() {
    if (enabled) {
        pidController.tick();
        return {true, 1};
    }
    else
        return {false, 100};   
}

void DosageController::enable() {
    enabled = true;
    pidController.setEnabled(true);
}

void DosageController::disable() {
    enabled = false;
    pidController.setEnabled(false);
    proportionalValve->setDutyCycle(0.0f); // Ensure valve is closed when PID is disabled
}

void DosageController::setTargetDosage(float dosage) {
	if (dosage > (settings->getDosageValue(settings->getSelectedProgram()) + settings->getMaxDosageVariationPercent()/100.0f*settings->getDosageValue(settings->getSelectedProgram()))){
	    targetDosage = settings->getDosageValue(settings->getSelectedProgram()) + settings->getMaxDosageVariationPercent()/100.0f*settings->getDosageValue(settings->getSelectedProgram());
    }
	else if (dosage < (settings->getDosageValue(settings->getSelectedProgram()) - settings->getMaxDosageVariationPercent()/100.0f*settings->getDosageValue(settings->getSelectedProgram()))){
	    targetDosage = settings->getDosageValue(settings->getSelectedProgram()) - settings->getMaxDosageVariationPercent()/100.0f*settings->getDosageValue(settings->getSelectedProgram());
    }
    else {
        targetDosage = dosage;
    }
    
    pidController.setTarget(targetDosage);
}

float DosageController::calculateDosage(){
    double temp = 0;
    
    if (settings->getNozzleCount() > 0 && settings->getNozzleDistance() > 0)
        temp = 60*flowmeter->getFlowRate()/settings->getNozzleCount()/settings->getNozzleDistance()*100.0f;
    if (settings->getSpeedSource() == SPEED_SOURCE::SIMULATION)
        currentDosage = temp / settings->getSimulationSpeed();
    else
        currentDosage = temp / gps->getSpeed();
    return currentDosage;
}
