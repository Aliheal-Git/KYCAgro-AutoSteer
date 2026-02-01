#include "Page.hpp"
#include "Window.hpp"
#include "Flowmeter.hpp"
#include "stdio.h"

#include "cmsis_os.h"

void InformationPage::render(){
    this->parentWindow->hideWindow();
	osDelay(10);
	this->parentWindow->clearWindow();
    this->parentWindow->writeString("Anlik debi", 0, 5);
    this->parentWindow->writeString("Kalan Tank hacmi", 2, 2);
    updateFlow();
    updateCapacity();
    this->parentWindow->showWindow();
}

bool InformationPage::task(){
    osDelay(100);
    updateFlow();
    updateCapacity();
    return true;
}

void InformationPage::handleButtonInput(ButtonQueueEvent event){
    switch (event.buttonType) {
    	case (ButtonType::MENU):
			switch(event.eventType){
				case (ButtonEventType::PRESSED):
					break;
				case (ButtonEventType::RELEASED):
					this->parentWindow->showPage(1);
					break;
				case (ButtonEventType::HELD):
					break;
			}
			break;
		case (ButtonType::PROGRAM):
			switch(event.eventType){
				case (ButtonEventType::PRESSED):
					break;
				case (ButtonEventType::RELEASED):
					this->parentWindow->showPage(1);
					break;
				case (ButtonEventType::HELD):
					break;
			}
			break;
    }
}

void InformationPage::updateFlow() {
    char buf[20];
    parentWindow->write("           ",  1, 11);
    parentWindow->write("<", 1, 5);
    snprintf(buf, sizeof(buf), "%.1f> L/dk", flowmeter.getFlowRate());
    parentWindow->write(buf, 1, 6);
}

void InformationPage::updateCapacity() {
    char buf[20];
    parentWindow->write("         ",  3, 11);
    parentWindow->write("<", 3, 5);
    snprintf(buf, sizeof(buf), "%.1f> L", flowmeter.getTotalVolume());
    parentWindow->write(buf, 3, 6);
}  