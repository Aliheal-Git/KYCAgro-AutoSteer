#include "Page.hpp"

#include "stdio.h"

using namespace App::Pages;

PageFuncResult InformationPage::render(){
    this->parentWindow->hideWindow();
	this->parentWindow->clearWindow();
    this->parentWindow->writeString("Anlik debi", 0, 5);
    this->parentWindow->writeString("Kalan Tank hacmi", 2, 2);
    updateFlow();
    updateCapacity();
    this->parentWindow->showWindow();
	return PageFuncResult{PageNavRequest::NONE, 0};
}

PageFuncResult InformationPage::update(){
    updateFlow();
    updateCapacity();
    return PageFuncResult{PageNavRequest::NONE, 200};
}

PageFuncResult InformationPage::handleButtonInput(ButtonQueueEvent event){
    switch (event.buttonType) {
    	case (ButtonType::MENU):
			switch(event.eventType){
				case (ButtonEventType::PRESSED):
					break;
				case (ButtonEventType::RELEASED):
					return {PageNavRequest::MAIN, 0};
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
					return {PageNavRequest::MAIN, 0};
					break;
				case (ButtonEventType::HELD):
					break;
			}
			break;
    }
	return {PageNavRequest::NONE, 0};
}

void InformationPage::updateFlow() {
    char buf[20];
    parentWindow->writeString("           ",  1, 11);
    parentWindow->writeString("<", 1, 5);
    snprintf(buf, sizeof(buf), "%.1f> L/dk", flowmeter->getFlowRate());
    parentWindow->writeString(buf, 1, 6);
}

void InformationPage::updateCapacity() {
    char buf[20];
    parentWindow->writeString("         ",  3, 11);
    parentWindow->writeString("<", 3, 5);
    snprintf(buf, sizeof(buf), "%.1f> L", flowmeter->getVolume());
    parentWindow->writeString(buf, 3, 6);
}  