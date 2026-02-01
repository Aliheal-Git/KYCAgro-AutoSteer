#include "Page.hpp"
#include "Window.hpp"
#include "Settings.hpp"
#include "Controller.hpp"

#include "cmsis_os.h"
#include <cstdio>


void ProgramsPage::render(){
    this->parentWindow->hideWindow();
	osDelay(10);
	this->parentWindow->clearWindow();
	osDelay(10);

    this->renderSelectedProgram();
    parentWindow->writeSpecial(customCharIndex::leftTriangleIndex, selectedItem, 0);
    this->parentWindow->write("Nozzle Cesidi", 1, 1);
    this->parentWindow->write("Dozaj Degeri", 2, 1);

    this->parentWindow->showWindow();
}

void ProgramsPage::handleButtonInput(ButtonQueueEvent event) {
    // Handle button inputs specific to the settings page
    switch (event.buttonType) {
        case ButtonType::PROGRAM:
            // Handle menu button
            switch (event.eventType) {
                case ButtonEventType::RELEASED:
                    // Navigate back to main page
                    if (inSubMenu) {
                        inSubMenu = false;
                        render();
                        return;
                    }
                    inSubMenu = true;
                    enterSetting();
                    break;
                case ButtonEventType::HELD:
                    // Navigate back to main page
                    if (!inSubMenu){
                        settings.writePageFlash();
                        controller.setTargetDosage(settings.getDosageValue(settings.getSelectedProgram()));
                        parentWindow->showPage(1);
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
    parentWindow->write(" ", selectedItem, 0); // Clear previous indicator
    selectedItem--;
    parentWindow->writeSpecial(customCharIndex::leftTriangleIndex, selectedItem, 0);
}

void ProgramsPage::updateSelectionIndicatorDown() {
    if (selectedItem == (itemCount-1)) {
        return; // Out of bounds
    }
    parentWindow->write(" ", selectedItem, 0); // Clear previous indicator
    selectedItem++;
    parentWindow->writeSpecial(customCharIndex::leftTriangleIndex, selectedItem, 0);
}

void ProgramsPage::renderSelectedProgram(){
    char buf[14];
    snprintf(buf, sizeof(buf), "<%d. Program>", settings.getSelectedProgram()+1);
    parentWindow->write(buf, 0, 4);
}

void ProgramsPage::enterSetting() {
    // Logic to enter the selected setting
    parentWindow->hideWindow();
    switch (selectedItem) {
        char buf[20];
        case 0:
            // Enter setting 1
            settings.setSelectedProgram(((settings.getSelectedProgram() + 1) <= 3) ? (settings.getSelectedProgram() + 1) : 0);
            renderSelectedProgram();
            inSubMenu = false;
            break;
        case 1:
            // Enter setting 2
            parentWindow->clearWindow();
            parentWindow->write("Nozzle Cesidi", 1, 3);
            parentWindow->write("                ", 2, 4);
            switch (settings.getSelectedNozzleType(settings.getSelectedProgram())) {
                case Settings::NOZZLE_TYPE::ISO01:
                    parentWindow->write("<ISO-01>", 2, 4);
                    break;
                case Settings::NOZZLE_TYPE::ISO015:
                    parentWindow->write("<ISO-015>", 2, 4);
                    break;
                case Settings::NOZZLE_TYPE::ISO02:
                    parentWindow->write("<ISO-02>", 2, 4);
                    break;
                case Settings::NOZZLE_TYPE::ISO025:
                    parentWindow->write("<ISO-025>", 2, 4);
                    break;
                case Settings::NOZZLE_TYPE::ISO03:
                    parentWindow->write("<ISO-03>", 2, 4);
                    break;
                case Settings::NOZZLE_TYPE::ISO04:
                    parentWindow->write("<ISO-04>", 2, 4);
                    break;
                case Settings::NOZZLE_TYPE::ISO05:
                    parentWindow->write("<ISO-05>", 2, 4);
                    break;
                case Settings::NOZZLE_TYPE::ISO06:
                    parentWindow->write("<ISO-06>", 2, 4);
                    break;
                case Settings::NOZZLE_TYPE::BRASS01:
                    parentWindow->write("<Pirinc-01>", 2, 4);
                    break;
                case Settings::NOZZLE_TYPE::BRASS012:
                    parentWindow->write("<Pirinc-012>", 2, 4);
                    break;
                case Settings::NOZZLE_TYPE::BRASS015:
                    parentWindow->write("<Pirinc-015>", 2, 4);
                    break;
                default:
                    break;
            }
            break;
        case 2:
            // Enter setting 3
            parentWindow->clearWindow();
            parentWindow->write("Dozaj Degeri", 1, 4);
            parentWindow->write("<", 2, 5);
        	snprintf(buf, sizeof(buf), "%.1f> L/Dnm", settings.getDosageValue(settings.getSelectedProgram()));
        	parentWindow->write(buf, 2, 6);
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
            settings.setSelectedNozzleType(settings.getSelectedNozzleType(settings.getSelectedProgram())+1, 
            settings.getSelectedProgram());
            parentWindow->write("                ", 2, 4);
            switch (settings.getSelectedNozzleType(settings.getSelectedProgram())) {
                case Settings::NOZZLE_TYPE::ISO01:
                    parentWindow->write("<ISO-01>", 2, 4);
                    break;
                case Settings::NOZZLE_TYPE::ISO015:
                    parentWindow->write("<ISO-015>", 2, 4);
                    break;
                case Settings::NOZZLE_TYPE::ISO02:
                    parentWindow->write("<ISO-02>", 2, 4);
                    break;
                case Settings::NOZZLE_TYPE::ISO025:
                    parentWindow->write("<ISO-025>", 2, 4);
                    break;
                case Settings::NOZZLE_TYPE::ISO03:
                    parentWindow->write("<ISO-03>", 2, 4);
                    break;
                case Settings::NOZZLE_TYPE::ISO04:
                    parentWindow->write("<ISO-04>", 2, 4);
                    break;
                case Settings::NOZZLE_TYPE::ISO05:
                    parentWindow->write("<ISO-05>", 2, 4);
                    break;
                case Settings::NOZZLE_TYPE::ISO06:
                    parentWindow->write("<ISO-06>", 2, 4);
                    break;
                case Settings::NOZZLE_TYPE::BRASS01:
                    parentWindow->write("<Pirinc-01>", 2, 4);
                    break;
                case Settings::NOZZLE_TYPE::BRASS012:
                    parentWindow->write("<Pirinc-012>", 2, 4);
                    break;
                case Settings::NOZZLE_TYPE::BRASS015:
                    parentWindow->write("<Pirinc-015>", 2, 4);
                    break;
                default:
                    break;
            }
            break;
        case 2:
            settings.setDosageValue(settings.getDosageValue(settings.getSelectedProgram()) + 0.1, settings.getSelectedProgram());
        	parentWindow->write("              ", 2, 5);
            parentWindow->write("<", 2, 5);
            snprintf(buf, sizeof(buf), "%.1f> L/Dnm", settings.getDosageValue(settings.getSelectedProgram()));
        	parentWindow->write(buf, 2, 6);
            break;
    }
}

void ProgramsPage::subMenuMinus(){
        switch (selectedItem) {
        char buf[20];
        case 0:
            break;
        case 1:
            settings.setSelectedNozzleType(settings.getSelectedNozzleType(settings.getSelectedProgram())-1, 
            settings.getSelectedProgram());
            parentWindow->write("                ", 2, 4);
            switch (settings.getSelectedNozzleType(settings.getSelectedProgram())) {
                case Settings::NOZZLE_TYPE::ISO01:
                    parentWindow->write("<ISO-01>", 2, 4);
                    break;
                case Settings::NOZZLE_TYPE::ISO015:
                    parentWindow->write("<ISO-015>", 2, 4);
                    break;
                case Settings::NOZZLE_TYPE::ISO02:
                    parentWindow->write("<ISO-02>", 2, 4);
                    break;
                case Settings::NOZZLE_TYPE::ISO025:
                    parentWindow->write("<ISO-025>", 2, 4);
                    break;
                case Settings::NOZZLE_TYPE::ISO03:
                    parentWindow->write("<ISO-03>", 2, 4);
                    break;
                case Settings::NOZZLE_TYPE::ISO04:
                    parentWindow->write("<ISO-04>", 2, 4);
                    break;
                case Settings::NOZZLE_TYPE::ISO05:
                    parentWindow->write("<ISO-05>", 2, 4);
                    break;
                case Settings::NOZZLE_TYPE::ISO06:
                    parentWindow->write("<ISO-06>", 2, 4);
                    break;
                case Settings::NOZZLE_TYPE::BRASS01:
                    parentWindow->write("<Pirinc-01>", 2, 4);
                    break;
                case Settings::NOZZLE_TYPE::BRASS012:
                    parentWindow->write("<Pirinc-012>", 2, 4);
                    break;
                case Settings::NOZZLE_TYPE::BRASS015:
                    parentWindow->write("<Pirinc-015>", 2, 4);
                    break;
                default:
                    break;
            }
            break;
        case 2:
            settings.setDosageValue(settings.getDosageValue(settings.getSelectedProgram()) - 0.1, settings.getSelectedProgram());
            parentWindow->write("              ", 2, 5);
            parentWindow->write("<", 2, 5);
        	snprintf(buf, sizeof(buf), "%.1f> L/Dnm", settings.getDosageValue(settings.getSelectedProgram()));
        	parentWindow->write(buf, 2, 6);
            break;
    }
}