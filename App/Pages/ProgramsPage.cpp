#include "Page.hpp"

#include <cstdint>
#include <cstdio>

using namespace App::Domain;
using namespace App::Pages;

PageFuncResult ProgramsPage::render(){
    this->parentWindow->hideWindow();
	this->parentWindow->clearWindow();
    this->renderSelectedProgram();
    parentWindow->writeCustomCharacter(customCharIndex::leftTriangleIndex, selectedItem, 0);
    this->parentWindow->writeString("Nozzle Cesidi", 1, 1);
    this->parentWindow->writeString("Dozaj Degeri", 2, 1);

    this->parentWindow->showWindow();
	return PageFuncResult{PageNavRequest::NONE, 0};
}

PageFuncResult ProgramsPage::handleButtonInput(ButtonQueueEvent event) {
    // Handle button inputs specific to the settings page
    switch (event.buttonType) {
        case ButtonType::PROGRAM:
            // Handle menu button
            switch (event.eventType) {
                case ButtonEventType::RELEASED:
                    if (inSubMenu) {
                        inSubMenu = false;
                        render();
                        return PageFuncResult{PageNavRequest::NONE, 0};
                    }
                    inSubMenu = true;
                    enterSetting();
                    break;
                case ButtonEventType::HELD:
                    // Navigate back to main page
                    if (!inSubMenu){
                        flash->writeData(SETTINGSBANKADRES, settings->getRawData(), sizeof(SettingsParameters));
                        return PageFuncResult{PageNavRequest::MAIN, 0};
                    }
                    break;
                default:
                    break;
            
            }

            break;
        case ButtonType::PLUS:
            // Handle plus button
            switch (event.eventType) {
                case ButtonEventType::PRESSED:
                    if (!inSubMenu)
                        updateSelectionIndicatorUp();
                    else
                        subMenuPlus();
                    break;
                case ButtonEventType::HELD:
                    if (inSubMenu)
                        subMenuPlus();
                    break;
                default:
                    break;
            }
            break;
        case ButtonType::MINUS:
            // Handle minus button
            switch (event.eventType) {
                case ButtonEventType::PRESSED:
                    // Move down
                    if(!inSubMenu)
                        updateSelectionIndicatorDown();
                    else
                        subMenuMinus();
                    break;
                default:
                    break;
                case ButtonEventType::HELD:
                    if (inSubMenu)
                        subMenuMinus();
                    break;
            }
            break;
        default:
            break;
    }
}

void ProgramsPage::updateSelectionIndicatorUp() {
    if (selectedItem <= 0) {
        return; // Out of bounds
    }
    parentWindow->writeString(" ", selectedItem, 0); // Clear previous indicator
    selectedItem--;
    parentWindow->writeCustomCharacter(customCharIndex::leftTriangleIndex, selectedItem, 0);
}

void ProgramsPage::updateSelectionIndicatorDown() {
    if (selectedItem == (itemCount-1)) {
        return; // Out of bounds
    }
    parentWindow->writeString(" ", selectedItem, 0); // Clear previous indicator
    selectedItem++;
    parentWindow->writeCustomCharacter(customCharIndex::leftTriangleIndex, selectedItem, 0);
}

void ProgramsPage::renderSelectedProgram(){
    char buf[14];
    snprintf(buf, sizeof(buf), "<%d. Program>", settings->getSelectedProgram()+1);
    parentWindow->writeString(buf, 0, 4);
}

void ProgramsPage::enterSetting() {
    // Logic to enter the selected setting
    parentWindow->hideWindow();
    switch (selectedItem) {
        char buf[20];
        case 0:
            // Enter setting 1
            settings->setSelectedProgram(((settings->getSelectedProgram() + 1) <= 3) ? (settings->getSelectedProgram() + 1) : 0);
            renderSelectedProgram();
            inSubMenu = false;
            break;
        case 1:
            // Enter setting 2
            parentWindow->clearWindow();
            parentWindow->writeString("Nozzle Cesidi", 1, 3);
            parentWindow->writeString("                ", 2, 4);
            switch (settings->getSelectedNozzleType(settings->getSelectedProgram())) {
                case NOZZLE_TYPE::ISO01:
                    parentWindow->writeString("<ISO-01>", 2, 4);
                    break;
                case NOZZLE_TYPE::ISO015:
                    parentWindow->writeString("<ISO-015>", 2, 4);
                    break;
                case NOZZLE_TYPE::ISO02:
                    parentWindow->writeString("<ISO-02>", 2, 4);
                    break;
                case NOZZLE_TYPE::ISO025:
                    parentWindow->writeString("<ISO-025>", 2, 4);
                    break;
                case NOZZLE_TYPE::ISO03:
                    parentWindow->writeString("<ISO-03>", 2, 4);
                    break;
                case NOZZLE_TYPE::ISO04:
                    parentWindow->writeString("<ISO-04>", 2, 4);
                    break;
                case NOZZLE_TYPE::ISO05:
                    parentWindow->writeString("<ISO-05>", 2, 4);
                    break;
                case NOZZLE_TYPE::ISO06:
                    parentWindow->writeString("<ISO-06>", 2, 4);
                    break;
                case NOZZLE_TYPE::BRASS01:
                    parentWindow->writeString("<Pirinc-01>", 2, 4);
                    break;
                case NOZZLE_TYPE::BRASS012:
                    parentWindow->writeString("<Pirinc-012>", 2, 4);
                    break;
                case NOZZLE_TYPE::BRASS015:
                    parentWindow->writeString("<Pirinc-015>", 2, 4);
                    break;
                default:
                    break;
            }
            break;
        case 2:
            // Enter setting 3
            parentWindow->clearWindow();
            parentWindow->writeString("Dozaj Degeri", 1, 4);
            parentWindow->writeString("<", 2, 5);
        	snprintf(buf, sizeof(buf), "%.1f> L/Dnm", settings->getDosageValue(settings->getSelectedProgram()));
        	parentWindow->writeString(buf, 2, 6);
            break;
    }
    parentWindow->showWindow();
}

void ProgramsPage::subMenuPlus(){
    switch (selectedItem) {
        char buf[20];
        case 0:
            break;
        case 1:
            if (settings->getSelectedNozzleType(settings->getSelectedProgram()) == NOZZLE_TYPE::BRASS015){
                settings->setSelectedNozzleType(NOZZLE_TYPE::ISO01, settings->getSelectedProgram());
            } else {
                settings->setSelectedNozzleType(static_cast<NOZZLE_TYPE>(static_cast<uint8_t>(settings->getSelectedNozzleType(settings->getSelectedProgram())) + 1), settings->getSelectedProgram());
            }
            parentWindow->writeString("                ", 2, 4);
            switch (settings->getSelectedNozzleType(settings->getSelectedProgram())) {
                case NOZZLE_TYPE::ISO01:
                    parentWindow->writeString("<ISO-01>", 2, 4);
                    break;
                case NOZZLE_TYPE::ISO015:
                    parentWindow->writeString("<ISO-015>", 2, 4);
                    break;
                case NOZZLE_TYPE::ISO02:
                    parentWindow->writeString("<ISO-02>", 2, 4);
                    break;
                case NOZZLE_TYPE::ISO025:
                    parentWindow->writeString("<ISO-025>", 2, 4);
                    break;
                case NOZZLE_TYPE::ISO03:
                    parentWindow->writeString("<ISO-03>", 2, 4);
                    break;
                case NOZZLE_TYPE::ISO04:
                    parentWindow->writeString("<ISO-04>", 2, 4);
                    break;
                case NOZZLE_TYPE::ISO05:
                    parentWindow->writeString("<ISO-05>", 2, 4);
                    break;
                case NOZZLE_TYPE::ISO06:
                    parentWindow->writeString("<ISO-06>", 2, 4);
                    break;
                case NOZZLE_TYPE::BRASS01:
                    parentWindow->writeString("<Pirinc-01>", 2, 4);
                    break;
                case NOZZLE_TYPE::BRASS012:
                    parentWindow->writeString("<Pirinc-012>", 2, 4);
                    break;
                case NOZZLE_TYPE::BRASS015:
                    parentWindow->writeString("<Pirinc-015>", 2, 4);
                    break;
                default:
                    break;
            }
            break;
        case 2:
        	parentWindow->writeString("              ", 2, 5);
            parentWindow->writeString("<", 2, 5);
            snprintf(buf, sizeof(buf), "%.1f> L/Dnm", settings->getDosageValue(settings->getSelectedProgram()));
        	parentWindow->writeString(buf, 2, 6);
            break;
    }
}

void ProgramsPage::subMenuMinus(){
        switch (selectedItem) {
        char buf[20];
        case 0:
            break;
        case 1:
            if (settings->getSelectedNozzleType(settings->getSelectedProgram()) == NOZZLE_TYPE::ISO01){
                settings->setSelectedNozzleType(NOZZLE_TYPE::BRASS015, settings->getSelectedProgram());
            } else {
                settings->setSelectedNozzleType(static_cast<NOZZLE_TYPE>(static_cast<uint8_t>(settings->getSelectedNozzleType(settings->getSelectedProgram())) - 1), settings->getSelectedProgram());
            }
            parentWindow->writeString("                ", 2, 4);
            switch (settings->getSelectedNozzleType(settings->getSelectedProgram())) {
                case NOZZLE_TYPE::ISO01:
                    parentWindow->writeString("<ISO-01>", 2, 4);
                    break;
                case NOZZLE_TYPE::ISO015:
                    parentWindow->writeString("<ISO-015>", 2, 4);
                    break;
                case NOZZLE_TYPE::ISO02:
                    parentWindow->writeString("<ISO-02>", 2, 4);
                    break;
                case NOZZLE_TYPE::ISO025:
                    parentWindow->writeString("<ISO-025>", 2, 4);
                    break;
                case NOZZLE_TYPE::ISO03:
                    parentWindow->writeString("<ISO-03>", 2, 4);
                    break;
                case NOZZLE_TYPE::ISO04:
                    parentWindow->writeString("<ISO-04>", 2, 4);
                    break;
                case NOZZLE_TYPE::ISO05:
                    parentWindow->writeString("<ISO-05>", 2, 4);
                    break;
                case NOZZLE_TYPE::ISO06:
                    parentWindow->writeString("<ISO-06>", 2, 4);
                    break;
                case NOZZLE_TYPE::BRASS01:
                    parentWindow->writeString("<Pirinc-01>", 2, 4);
                    break;
                case NOZZLE_TYPE::BRASS012:
                    parentWindow->writeString("<Pirinc-012>", 2, 4);
                    break;
                case NOZZLE_TYPE::BRASS015:
                    parentWindow->writeString("<Pirinc-015>", 2, 4);
                    break;
                default:
                    break;
            }
            break;
        case 2:
            settings->setDosageValue(settings->getDosageValue(settings->getSelectedProgram()) - 0.1, settings->getSelectedProgram());
            parentWindow->writeString("              ", 2, 5);
            parentWindow->writeString("<", 2, 5);
        	snprintf(buf, sizeof(buf), "%.1f> L/Dnm", settings->getDosageValue(settings->getSelectedProgram()));
        	parentWindow->writeString(buf, 2, 6);
            break;
    }
}