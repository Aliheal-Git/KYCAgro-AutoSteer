#include "Page.hpp"

#include <cstdint>
#include <cstdio>

using namespace App::Domain;
using namespace App::Pages;

PageFuncResult MainPage::update(){
	setUISpeed(gpsDevice->getSpeed());
	if (dosageController->getMode() == DosageControllerMode::AUTO)
		setTargetDosage(dosageController->getTargetDosage());
	dosageSum += dosageController->getDosage();
	if (taskStep >= dosageSampleCount){
		taskStep = 0;
		setUIDosage(dosageSum/dosageSampleCount);
		dosageSum = 0;
	}

	for (uint8_t i = 0; i < settings.getNozzleValveCount(); i++){
		bool valveState = valveController->getValveState(i) == ValveState::OPEN;
		if (valveState)
			setUIValveOn(i);
		else
			setUIValveOff(i);
	}
	
	taskStep++;
	return {PageNavRequest::NONE, 100};
}

PageFuncResult MainPage::handleButtonInput(ButtonQueueEvent event){
	switch (event.buttonType){
		case (ButtonType::GPS):
			switch(event.eventType){
				case (ButtonEventType::PRESSED):
					this->setGPSAuto();
					break;
				case (ButtonEventType::RELEASED):
					this->setGPSManual();
					break;
				case (ButtonEventType::HELD):
					break;
			}
			break;
		case (ButtonType::DOSAGE):
			switch(event.eventType){
				case (ButtonEventType::PRESSED):
					this->setDosageModeAuto();
					break;
				case (ButtonEventType::RELEASED):
					this->setDosageModeManual();
					break;
				case (ButtonEventType::HELD):
					break;
			}
			break;
		case (ButtonType::MENU):
			switch(event.eventType){
				case (ButtonEventType::PRESSED):
					break;
				case (ButtonEventType::RELEASED):
					return {PageNavRequest::NEXT, 0};
					break;
				case (ButtonEventType::HELD):
					// if (buttons.BUTTON_PROGRAM._button.state == OCS_DOWN || buttons.BUTTON_PROGRAM._button.state == OCS_PRESS)
					// 	this->parentWindow->showPage(4);
					break;
			}
			break;
		case (ButtonType::PROGRAM):
			switch(event.eventType){
				case (ButtonEventType::PRESSED):
					break;
				case (ButtonEventType::RELEASED):
					return {PageNavRequest::PROGRAMS, 0};
					break;
				case (ButtonEventType::HELD):
					// if (buttons.BUTTON_MENU._button.state == OCS_DOWN || buttons.BUTTON_MENU._button.state == OCS_PRESS)
					// 	this->parentWindow->showPage(4);
					break;
			}
			break;
	}
}

PageFuncResult MainPage::render(){
	if (renderStep < 1){
		this->parentWindow->hideWindow();
		this->parentWindow->clearWindow();
		renderStep++;
		return {PageNavRequest::NONE, 10};
	} else if (renderStep < 2){
		if (settings.getSpeedSource() == SPEED_SOURCE::GPS)
			this->parentWindow->writeString("GPS", 0, 5);
		else
			this->parentWindow->writeString("SIM", 0, 5);
	}

	this->setSelectedProgram();


	this->parentWindow->writeString("Km/h", 0, 15);
	if (dosageController->getMode() == DosageControllerMode::AUTO)
		this->setDosageModeAuto();
	else
		this->setDosageModeManual();
	this->setGPSManual();
	this->parentWindow->writeString("L/Dnm", 1, 15);

	for (uint8_t i = 0; i < settings.getNozzleValveCount(); i++){
		char buf[4];   // enough for 0–255 + null
		snprintf(buf, sizeof(buf), "%u", i);
		this->parentWindow->writeString(buf, 2, 5);
		uiValveStates[i] = 0;
		if (valveController->getValveState(i) == ValveState::OPEN){
			this->setUIValveOn(i);
		} 
		else {
			this->setUIValveOff(i);
		}
	}

	setUISpeed(gpsDevice->getSpeed());
	setUIDosage(dosageController->getDosage());
	setTargetDosage(dosageController->getTargetDosage());

	if (valveController->getMode() == ValveControllerMode::MANUAL)
		setGPSManual();
	else
		setGPSAuto();

	this->parentWindow->showWindow();
	return {PageNavRequest::NONE, 100};
}

void MainPage::setGPSAuto(){
	this->parentWindow->writeString("A", 3, 2);
	for (uint8_t i = 0; i < settings.getNozzleValveCount(); i++){
		if (valveController->getValveState(i) == ValveState::OPEN)
			this->setUIValveOn(i);
		else
			this->setUIValveOff(i);
	}
}

void MainPage::setGPSManual(){
	this->parentWindow->writeString("M", 3, 2);
	for (uint8_t i = 0; i < settings.getNozzleValveCount(); i++){
		if (valveController->getValveState(i) == ValveState::OPEN)
			this->setUIValveOn(i);
		else
			this->setUIValveOff(i);
	}
}

void MainPage::setDosageModeAuto(){
	this->parentWindow->writeString("SET()", 1, 0);
	this->setTargetDosage(dosageController->getTargetDosage());
}

void MainPage::setDosageModeManual(){
	this->parentWindow->writeString("         ", 1, 0);
	this->parentWindow->writeString("Manuel", 1, 0);
}

void MainPage::setUIDosage(float dosage){
	if (dosage == uiDosage)
		return;
	char buf[5];
	snprintf(buf, sizeof(buf), "%4.1f", dosage);
	this->parentWindow->writeString(buf, 1, 10);
	this->uiDosage = dosage;
}

void MainPage::setUISpeed(float speed){
	if (speed == uiSpeed)
		return;
	char buf[5];
	snprintf(buf, sizeof(buf), "%4.1f", speed);
	this->parentWindow->writeString(buf, 0, 10);
	this->uiSpeed = speed;
}

void MainPage::setTargetDosage(float target_dosage){
	if (target_dosage == uiTargetDosage)
		return;
	char buf[8];
	if (settings.getDosageValue(settings.getSelectedProgram()) > (target_dosage + 0.01f))
		snprintf(buf, sizeof(buf), "%3.1f)-", target_dosage);
	else if (settings.getDosageValue(settings.getSelectedProgram()) < (target_dosage - 0.01f))
		snprintf(buf, sizeof(buf), "%3.1f)+", target_dosage);
	else
		snprintf(buf, sizeof(buf), "%3.1f) ", target_dosage);
	if (dosageController->getMode() == DosageControllerMode::AUTO)
		this->parentWindow->writeString(buf, 1, 4);
}

void MainPage::setUIValveOn(uint8_t valveIndex){
	if (!uiValveStates[valveIndex]){
		this->parentWindow->writeCustomCharacter(customCharIndex::rainDropIndex, 3, 5+2*valveIndex);
		uiValveStates[valveIndex] = true;
	}
}

void MainPage::setUIValveOff(uint8_t valveIndex){
	if (uiValveStates[valveIndex]){
		this->parentWindow->writeString(" ", 3, 5+2*valveIndex);
		uiValveStates[valveIndex] = false;
	}
}

void MainPage::setSelectedProgram(){
	char buf[4];
	snprintf(buf, sizeof(buf), "P%d", settings.getSelectedProgram()+1);
	this->parentWindow->writeString(buf, 0, 1);
}
