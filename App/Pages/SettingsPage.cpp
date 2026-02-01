#include "Page.hpp"

#include <cstdint>
#include <cstring>
#include <cstdio>

using namespace App::Pages;

PageFuncResult SettingsPage::render() {
    // Render the settings page UI
    parentWindow->hideWindow();
    parentWindow->clearWindow();
    parentWindow->writeString(items[rollOverCount*maxVisibleItems], 0, 1);
    parentWindow->writeString(items[rollOverCount*maxVisibleItems + 1], 1, 1);
    parentWindow->writeString(items[rollOverCount*maxVisibleItems + 2], 2, 1); 
    parentWindow->writeString(items[rollOverCount*maxVisibleItems + 3], 3, 1);
    parentWindow->writeCustomCharacter(customCharIndex::leftTriangleIndex, selectedItem%4, 0);
    parentWindow->showWindow();
    return PageFuncResult{PageNavRequest::NONE, 0};
}

void SettingsPage::updateSelectionIndicatorUp() {
    if (selectedItem <= 0) {
        return; // Out of bounds
    }
    parentWindow->writeString(" ", selectedItem%maxVisibleItems, 0); // Clear previous indicator
    selectedItem--;
    uint8_t temp = selectedItem / maxVisibleItems;
    if (rollOverCount != temp) {
        rollOverCount = temp;
        render(); // Re-render the page if we rolled over
        return;
    }
    parentWindow->writeCustomCharacter(customCharIndex::leftTriangleIndex, selectedItem%maxVisibleItems, 0);
}

void SettingsPage::updateSelectionIndicatorDown() {
    if (selectedItem == (itemCount-1)) {
        return; // Out of bounds
    }
    parentWindow->writeString(" ", selectedItem%maxVisibleItems, 0); // Clear previous indicator
    selectedItem++;
    uint8_t temp = selectedItem / maxVisibleItems;
    if (rollOverCount != temp) {
        rollOverCount = temp;
        render(); // Re-render the page if we rolled over
        return;
    }
    rollOverCount = selectedItem / maxVisibleItems;
    parentWindow->writeCustomCharacter(customCharIndex::leftTriangleIndex, selectedItem%maxVisibleItems, 0);
}

void SettingsPage::enterSetting() {
    // Logic to enter the selected setting
    parentWindow->hideWindow();
    parentWindow->clearWindow();
    parentWindow->writeString(items[selectedItem], 1, (parentWindow->getColumnCount()-strlen(items[selectedItem]))/2);

    switch (selectedItem) {
        char buf[20];
        case 0:
            // Enter setting 1
            parentWindow->writeString("Turkce", 2, 2);
            parentWindow->writeString("English", 2, 11);
            break;
        case 1:
            // Enter setting 2
        	parentWindow->writeString("<", 2, 8);
        	snprintf(buf, sizeof(buf), "%d>", settings->getNozzleCount());
        	parentWindow->writeString(buf, 2, 9);
            break;
        case 2:
            // Enter setting 3
            parentWindow->writeString("<", 2, 6);
        	snprintf(buf, sizeof(buf), "%.1f> cm", settings->getNozzleDistance());
        	parentWindow->writeString(buf, 2, 7);
            break;
        case 3:
            // Enter setting 4
            parentWindow->writeString("<", 2, 8);
        	snprintf(buf, sizeof(buf), "%d>", settings->getFlowMeterCoefficient());
        	parentWindow->writeString(buf, 2, 9);
            break;
        case 4:
            // Enter setting 5
            parentWindow->writeString("<", 2, 5);
        	snprintf(buf, sizeof(buf), "%.1f> L/dk", settings->getMinDosage());
        	parentWindow->writeString(buf, 2, 6);
            break;
        case 5:
            // Enter setting 6
            parentWindow->writeString("<", 2, 5);
        	snprintf(buf, sizeof(buf), "%.1f> L/dk", settings->getMaxDosage());
        	parentWindow->writeString(buf, 2, 6);
            break;
        case 6:
            // Enter setting 7
            parentWindow->writeString("<", 2, 7);
        	snprintf(buf, sizeof(buf), "%%%.1f>", settings->getMaxDosageVariationPercent());
        	parentWindow->writeString(buf, 2, 8);
            break;
        case 7:
            // Enter setting 8
            parentWindow->writeString("<", 2, 7);
        	snprintf(buf, sizeof(buf), "%.1f> L", settings->getTankCapacity());
        	parentWindow->writeString(buf, 2, 8);
            break;
        case 8:
            // Enter setting 9
            if(settings->getSpeedSource() == SPEED_SOURCE::GPS)
                parentWindow->writeString(">", 2, 2);
            else
                parentWindow->writeString(">", 2, 8);;
            parentWindow->writeString("GPS", 2, 3);
        	parentWindow->writeString("SIMULASYON", 2, 9);
            break;
        case 9:
            // Enter setting 10
            parentWindow->writeString("<", 2, 5);
        	snprintf(buf, sizeof(buf), "%.1f km/h>", settings->getSimulationSpeed());
        	parentWindow->writeString(buf, 2, 6);
            break;
        default:
            break;
    }
    parentWindow->showWindow();
}


PageFuncResult SettingsPage::handleButtonInput(ButtonQueueEvent event) {
    // Handle button inputs specific to the settings page
    switch (event.buttonType) {
        case ButtonType::MENU:
            // Handle menu button
            switch (event.eventType) {
                case ButtonEventType::RELEASED:
                    // Navigate back to main page
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
                        selectedItem = 0;
                        rollOverCount = 0;
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
                    // Move up
                    if (inSubMenu){
                        subMenuPlus();
                    }
                    else
                        updateSelectionIndicatorUp();
                    break;
                case ButtonEventType::HELD:
                    if (inSubMenu){
                        subMenuPlus();
                    }
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
                    if (inSubMenu){
                        subMenuMinus();
                    }
                    else
                        updateSelectionIndicatorDown();
                    break;
                default:
                    break;
                case ButtonEventType::HELD:
                    if (inSubMenu){
                        subMenuMinus();
                    }
                    break;
            }
            break;
        default:
            break;
    }
    return PageFuncResult{PageNavRequest::NONE, 0};
}

void SettingsPage::subMenuMinus(){
    switch (selectedItem) {
        char buf[20];
        case 0:
            // Enter setting 1
            parentWindow->writeString("Turkce", 2, 2);
            parentWindow->writeString("English", 2, 11);
            break;
        case 1:
            // Enter setting 2
            parentWindow->writeString("         ",  2, 8);
            parentWindow->writeString("<", 2, 8);
            settings->setNozzleCount(settings->getNozzleCount()-1);
        	snprintf(buf, sizeof(buf), "%d>", settings->getNozzleCount());
        	parentWindow->writeString(buf, 2, 9);
            break;
        case 2:
            // Enter setting 3
            parentWindow->writeString("         ",  2, 6);
            parentWindow->writeString("<", 2, 6);
            settings->setNozzleDistance(settings->getNozzleDistance()-0.1f);
        	snprintf(buf, sizeof(buf), "%.1f> cm", settings->getNozzleDistance());
        	parentWindow->writeString(buf, 2, 7);
            break;
        case 3:
            // Enter setting 4
            parentWindow->writeString("         ",  2, 8);
            parentWindow->writeString("<", 2, 8);
            settings->setFlowMeterCoefficient(settings->getFlowMeterCoefficient()-1);
        	snprintf(buf, sizeof(buf), "%d>", settings->getFlowMeterCoefficient());
        	parentWindow->writeString(buf, 2, 9);
            break;
        case 4:
            // Enter setting 5
            parentWindow->writeString("           ",  2, 5);
            parentWindow->writeString("<", 2, 5);
            settings->setMinDosage(settings->getMinDosage()-0.1);
        	snprintf(buf, sizeof(buf), "%.1f> L/dk", settings->getMinDosage());
        	parentWindow->writeString(buf, 2, 6);
            break;
        case 5:
            // Enter setting 6
            parentWindow->writeString("           ",  2, 5);
            parentWindow->writeString("<", 2, 5);
            settings->setMaxDosage(settings->getMaxDosage()-0.1);
        	snprintf(buf, sizeof(buf), "%.1f> L/dk", settings->getMaxDosage());
        	parentWindow->writeString(buf, 2, 6);
            break;
        case 6:
            // Enter setting 7
            parentWindow->writeString("         ",  2, 7);
            parentWindow->writeString("<", 2, 7);
            settings->setMaxDosageVariationPercent(settings->getMaxDosageVariationPercent()-10.0);
        	snprintf(buf, sizeof(buf), "%%%.1f>", settings->getMaxDosageVariationPercent());
        	parentWindow->writeString(buf, 2, 8);
            break;
        case 7:
            // Enter setting 8
            parentWindow->writeString("         ",  2, 7);
            parentWindow->writeString("<", 2, 7);
            settings->setTankCapacity(settings->getTankCapacity()-100.0);
        	snprintf(buf, sizeof(buf), "%.1f> L", settings->getTankCapacity());
        	parentWindow->writeString(buf, 2, 8);
            break;
        case 8:
            // Enter setting 9
            parentWindow->writeString(" ", 2, 8);
            parentWindow->writeString(">", 2, 2);
            settings->setSpeedSource(SPEED_SOURCE::GPS);
            break;
        case 9:
            // Enter setting 10
            parentWindow->writeString("         ",  2, 5);
            parentWindow->writeString("<", 2, 5);
            settings->setSimulationSpeed(settings->getSimulationSpeed()-0.1);
        	snprintf(buf, sizeof(buf), "%.1f km/h>", settings->getSimulationSpeed());
        	parentWindow->writeString(buf, 2, 6);
            break;
        default:
            break;
    }
}

void SettingsPage::subMenuPlus(){
    switch (selectedItem) {
        char buf[20];
        case 0:
            // Enter setting 1
            parentWindow->writeString("Turkce", 2, 2);
            parentWindow->writeString("English", 2, 11);
            break;
        case 1:
            // Enter setting 2
            parentWindow->writeString("         ",  2, 8);
            parentWindow->writeString("<", 2, 8);
            settings->setNozzleCount(settings->getNozzleCount()+1);
        	snprintf(buf, sizeof(buf), "%d>", settings->getNozzleCount());
        	parentWindow->writeString(buf, 2, 9);
            break;
        case 2:
            // Enter setting 3
            parentWindow->writeString("         ",  2, 6);
            parentWindow->writeString("<", 2, 6);
            settings->setNozzleDistance(settings->getNozzleDistance()+0.1f);
        	snprintf(buf, sizeof(buf), "%.1f> cm", settings->getNozzleDistance());
        	parentWindow->writeString(buf, 2, 7);
            break;
        case 3:
            // Enter setting 4
            parentWindow->writeString("         ",  2, 8);
            parentWindow->writeString("<", 2, 8);
            settings->setFlowMeterCoefficient(settings->getFlowMeterCoefficient()+1);
        	snprintf(buf, sizeof(buf), "%d>", settings->getFlowMeterCoefficient());
        	parentWindow->writeString(buf, 2, 9);
            break;
        case 4:
            // Enter setting 5
            parentWindow->writeString("           ",  2, 5);
            parentWindow->writeString("<", 2, 5);
            settings->setMinDosage(settings->getMinDosage()+0.1);
        	snprintf(buf, sizeof(buf), "%.1f> L/dk", settings->getMinDosage());
        	parentWindow->writeString(buf, 2, 6);
            break;
        case 5:
            // Enter setting 6
            parentWindow->writeString("           ",  2, 5);
            parentWindow->writeString("<", 2, 5);
            settings->setMaxDosage(settings->getMaxDosage()+0.1);
        	snprintf(buf, sizeof(buf), "%.1f> L/dk", settings->getMaxDosage());
        	parentWindow->writeString(buf, 2, 6);
            break;
        case 6:
            // Enter setting 7
            parentWindow->writeString("         ",  2, 7);
            parentWindow->writeString("<", 2, 7);
            settings->setMaxDosageVariationPercent(settings->getMaxDosageVariationPercent()+10.0);
        	snprintf(buf, sizeof(buf), "%%%.1f>", settings->getMaxDosageVariationPercent());
        	parentWindow->writeString(buf, 2, 8);
            break;
        case 7:
            // Enter setting 8
            parentWindow->writeString("         ",  2, 7);
            parentWindow->writeString("<", 2, 7);
            settings->setTankCapacity(settings->getTankCapacity()+100.0);
            flowmeter->setTankCapacity(settings->getTankCapacity());
        	snprintf(buf, sizeof(buf), "%.1f> L", settings->getTankCapacity());
        	parentWindow->writeString(buf, 2, 8);
            break;
        case 8:
            // Enter setting 9
            parentWindow->writeString(" ", 2, 2);
            parentWindow->writeString(">", 2, 8);
            settings->setSpeedSource(SPEED_SOURCE::SIMULATION);
            break;
        case 9:
            // Enter setting 10
            parentWindow->writeString("            ",  2, 5);
            parentWindow->writeString("<", 2, 5);
            settings->setSimulationSpeed(settings->getSimulationSpeed()+0.1);
        	snprintf(buf, sizeof(buf), "%.1f km/h>", settings->getSimulationSpeed());
        	parentWindow->writeString(buf, 2, 6);
            break;
        default:
            break;
    }
}