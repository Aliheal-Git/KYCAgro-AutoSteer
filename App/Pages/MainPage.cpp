
#include "Page.hpp"
#include "WindowCommon.hpp"
#include "SettingsCommon.hpp"

#include <cstdint>

using namespace App::Domain::WindowCommon;
using namespace App::Domain::SettingsCommon;

PageFuncResult MainPage::task(){
	// if (_speed != controller.getSpeed())
	// 	setSpeed(controller.getSpeed());

	dosageSum += controller.getDosage();
	if (taskStep >= 20){
		taskStep = 0;
		setDosage(dosageSum/20.0f);
		dosageSum = 0;
	}


	for (uint8_t i = 0; i < controller.maxValve; i++){
		if (Valves[i].getMode() == Valve::AUTO){
			if (Valves[i].getStatus() == Valve::OPEN)
				setValveOn(i);
			else
			 	setValveOff(i);
		}
	}
	
	taskStep++;
	return {PageNavRequest::NONE, 200};
}

void MainPage::handleButtonInput(ButtonQueueEvent event){
	switch (event.buttonType){
		case (ButtonType::MAIN):
			switch(event.eventType){
				case (ButtonEventType::PRESSED):
					break;
				case (ButtonEventType::RELEASED):
					break;
				case (ButtonEventType::HELD):
					break;
			}
			break;
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
		case (ButtonType::DOSAGEMODE):
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
					this->parentWindow->nextPage();
					break;
				case (ButtonEventType::HELD):
					if (buttons.BUTTON_PROGRAM._button.state == OCS_DOWN || buttons.BUTTON_PROGRAM._button.state == OCS_PRESS)
						this->parentWindow->showPage(4);
					break;
			}
			break;
		case (ButtonType::PROGRAM):
			switch(event.eventType){
				case (ButtonEventType::PRESSED):
					break;
				case (ButtonEventType::RELEASED):
					this->parentWindow->showPage(3);
					break;
				case (ButtonEventType::HELD):
					if (buttons.BUTTON_MENU._button.state == OCS_DOWN || buttons.BUTTON_MENU._button.state == OCS_PRESS)
						this->parentWindow->showPage(4);
					break;
			}
			break;
		case (ButtonType::PLUS):
			switch(event.eventType){
				case (ButtonEventType::PRESSED):
					if (controller.getMode() == Controller::Mode::AUTO)
						this->setTargetDosage(controller.getTargetDosage() + settings.getDosageValue(settings.getSelectedProgram())*0.1);
					else
					{
					 	propValve.setDutyCycle(1.0);
					}
					break;
				case (ButtonEventType::RELEASED):
					if (controller.getMode() == Controller::Mode::MANUAL)
					{
						propValve.setDutyCycle(0.0);
					}
					break;	
				case (ButtonEventType::HELD):
					if (controller.getMode() == Controller::Mode::AUTO)
						this->setTargetDosage(controller.getTargetDosage() + settings.getDosageValue(settings.getSelectedProgram())*0.1);
					break;
			}
			break;
		case (ButtonType::MINUS):
			switch(event.eventType){
				case (ButtonEventType::PRESSED):
					if (controller.getMode() == Controller::Mode::AUTO)
						this->setTargetDosage(controller.getTargetDosage() - settings.getDosageValue(settings.getSelectedProgram())*0.1);
					else
					{
					 	propValve.setDutyCycle(-1.0);
					}
					break;
				case (ButtonEventType::RELEASED):
					if (controller.getMode() == Controller::Mode::MANUAL)
					{
						propValve.setDutyCycle(0.0);
					}
					break;
				case (ButtonEventType::HELD):
					if (controller.getMode() == Controller::Mode::AUTO)
						this->setTargetDosage(controller.getTargetDosage() - settings.getDosageValue(settings.getSelectedProgram())*0.1);
					break;
			}
			break;
		case (ButtonType::VALVE1):
			switch(event.eventType){
				case (ButtonEventType::PRESSED):
					this->setValveOn(0);
					break;
				case (ButtonEventType::RELEASED):
				    this->setValveOff(0);
					break;
				case (ButtonEventType::HELD):
					break;
			}
			break;
		case (ButtonType::VALVE2):
			switch(event.eventType){
				case (ButtonEventType::PRESSED):
					this->setValveOn(1);
					break;
				case (ButtonEventType::RELEASED):
					this->setValveOff(1);
					break;
				case (ButtonEventType::HELD):
					break;
			}
				break;
		case (ButtonType::VALVE3):
			switch(event.eventType){
				case (ButtonEventType::PRESSED):
					this->setValveOn(2);
					break;
				case (ButtonEventType::RELEASED):
					this->setValveOff(2);
					break;
				case (ButtonEventType::HELD):
					break;
			}
				break;
		case (ButtonType::VALVE4):
			switch(event.eventType){
				case (ButtonEventType::PRESSED):
					this->setValveOn(3);
					break;
				case (ButtonEventType::RELEASED):
					this->setValveOff(3);
					break;
				case (ButtonEventType::HELD):
					break;
			}
				break;
		case (ButtonType::VALVE5):
			switch(event.eventType){
				case (ButtonEventType::PRESSED):
					this->setValveOn(4);
					break;
				case (ButtonEventType::RELEASED):
					this->setValveOff(4);
					break;
				case (ButtonEventType::HELD):
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
	} else 
	if (renderStep < 2){
		if (settings.getSpeedSource() == SPEED_SOURCE::GPS)
			this->parentWindow->writeString("GPS", 0, 5);
		else
			this->parentWindow->writeString("SIM", 0, 5);
	}

	setSelectedProgram();


	this->parentWindow->write("Km/h", 0, 15);
	if (controller.getMode() == Controller::AUTO)
		this->setDosageModeAuto();
	else
		this->setDosageModeManual();
	this->setGPSManual();
	this->parentWindow->write("L/Dnm", 1, 15);
	this->parentWindow->write("1", 2, 5);
	this->parentWindow->write("2", 2, 7);
	this->parentWindow->write("3", 2, 9);
	this->parentWindow->write("4", 2, 11);
	this->parentWindow->write("5", 2, 13);
	setSpeed(controller.getSpeed());
	setDosage(controller.getDosage());
	setTargetDosage(controller.getTargetDosage());
	uint8_t sum = 0;

	if (buttons.BUTTON_GPS._button.state == OCS_INIT){
		for (uint8_t i = 0; i < controller.maxValve; i++)
			Valves[i].setMode(Valve::Mode::MANUAL);
		mainValve.setMode(Valve::Mode::MANUAL);
		setGPSManual();
	}


	for (uint8_t i = 0; i < controller.maxValve; i++){
		if (Valves[i].getStatus() == Valve::Status::OPEN)
			sum++;
	}
	if (sum == 0)
		mainValve.close(Valve::Mode::MANUAL);

	this->parentWindow->showWindow();
}

void MainPage::setGPSAuto(){
	this->parentWindow->write("A", 3, 2);
	for (uint8_t i = 0; i < this->parentWindow->maxValve; i++){
		if (Valves[i].getStatus() == Valve::OPEN)
			this->setValveOn(i);
		else
			this->setValveOff(i);
	}
}

void MainPage::setGPSManual(){
	this->parentWindow->write("M", 3, 2);
	for (uint8_t i = 0; i < this->parentWindow->maxValve; i++){
		if (Valves[i].getStatus())
			this->setValveOn(i);
		else
			this->setValveOff(i);
	}
}

void MainPage::setDosageModeAuto(){
	this->parentWindow->write("SET()", 1, 0);
	this->setTargetDosage(controller.getTargetDosage());
	controller.enablePIDController();
}

void MainPage::setDosageModeManual(){
	this->parentWindow->write("         ", 1, 0);
	this->parentWindow->write("Manuel", 1, 0);
	controller.disablePIDController();
}

void MainPage::setDosage(float dosage){
	char buf[5];
	snprintf(buf, sizeof(buf), "%4.1f", dosage);
	this->parentWindow->write(buf, 1, 10);
	this->_dosage = dosage;
}

void MainPage::setSpeed(float speed){
	char buf[5];
	snprintf(buf, sizeof(buf), "%4.1f", speed);
	this->parentWindow->write(buf, 0, 10);
	this->_speed = speed;
}

void MainPage::setTargetDosage(float target_dosage){
	char buf[8];
	controller.setTargetDosage(target_dosage);
	if (settings.getDosageValue(settings.getSelectedProgram()) > (controller.getTargetDosage() + 0.01f))
		snprintf(buf, sizeof(buf), "%3.1f)-", controller.getTargetDosage());
	else if (settings.getDosageValue(settings.getSelectedProgram()) < (controller.getTargetDosage() - 0.01f))
		snprintf(buf, sizeof(buf), "%3.1f)+", controller.getTargetDosage());
	else
		snprintf(buf, sizeof(buf), "%3.1f) ", controller.getTargetDosage());
	if (controller.getMode() == Controller::AUTO)
		this->parentWindow->write(buf, 1, 4);
}

void MainPage::setValveOn(uint8_t valveIndex){
	if (Valves[valveIndex].getStatus() == Valve::OPEN)
		this->parentWindow->writeSpecial(rainDropIndex, 3, 5+2*valveIndex);
}

void MainPage::setValveOff(uint8_t valveIndex){
	if (Valves[valveIndex].getStatus() == Valve::CLOSED)
		this->parentWindow->write(" ", 3, 5+2*valveIndex);
}

void MainPage::setSelectedProgram(){
	char buf[4];
	snprintf(buf, sizeof(buf), "P%d", settings.getSelectedProgram()+1);
	this->parentWindow->write(buf, 0, 1);
}
