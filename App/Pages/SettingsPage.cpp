/*
 * SettingsPage.cpp
 *
 *  Created on: Sep 20, 2025
 *      Author: alica
 */

#include "ButtonsGlobal.h"
#include "Page.hpp"
#include "Window.hpp"
#include "Settings.hpp"
#include "Flowmeter.hpp"

#include "cmsis_os.h"
#include "customchars.h"
#include <cstdint>
#include <cstring>
#include <cstdio>

void SettingsPage::render() {
    // Render the settings page UI
    parentWindow->hideWindow();
    parentWindow->clearWindow();
    parentWindow->write(items[rollOverCount*maxVisibleItems], 0, 1);
    parentWindow->write(items[rollOverCount*maxVisibleItems + 1], 1, 1);
    parentWindow->write(items[rollOverCount*maxVisibleItems + 2], 2, 1); 
    parentWindow->write(items[rollOverCount*maxVisibleItems + 3], 3, 1);
    parentWindow->writeSpecial(customCharIndex::leftTriangleIndex, selectedItem%4, 0);
    parentWindow->showWindow();
}

void SettingsPage::updateSelectionIndicatorUp() {
    if (selectedItem <= 0) {
        return; // Out of bounds
    }
    parentWindow->write(" ", selectedItem%maxVisibleItems, 0); // Clear previous indicator
    selectedItem--;
    uint8_t temp = selectedItem / maxVisibleItems;
    if (rollOverCount != temp) {
        rollOverCount = temp;
        render(); // Re-render the page if we rolled over
        return;
    }
    parentWindow->writeSpecial(customCharIndex::leftTriangleIndex, selectedItem%maxVisibleItems, 0);
}

void SettingsPage::updateSelectionIndicatorDown() {
    if (selectedItem == (itemCount-1)) {
        return; // Out of bounds
    }
    parentWindow->write(" ", selectedItem%maxVisibleItems, 0); // Clear previous indicator
    selectedItem++;
    uint8_t temp = selectedItem / maxVisibleItems;
    if (rollOverCount != temp) {
        rollOverCount = temp;
        render(); // Re-render the page if we rolled over
        return;
    }
    rollOverCount = selectedItem / maxVisibleItems;
    parentWindow->writeSpecial(customCharIndex::leftTriangleIndex, selectedItem%maxVisibleItems, 0);
}

void SettingsPage::enterSetting() {
    // Logic to enter the selected setting
    parentWindow->hideWindow();
    parentWindow->clearWindow();
    parentWindow->write(items[selectedItem], 1, (parentWindow->maxColumn-strlen(items[selectedItem]))/2);

    switch (selectedItem) {
        char buf[20];
        case 0:
            // Enter setting 1
            parentWindow->write("Turkce", 2, 2);
            parentWindow->write("English", 2, 11);
            break;
        case 1:
            // Enter setting 2
        	parentWindow->write("<", 2, 8);
        	snprintf(buf, sizeof(buf), "%d>", settings.getNozzleCount());
        	parentWindow->write(buf, 2, 9);
            break;
        case 2:
            // Enter setting 3
            parentWindow->write("<", 2, 6);
        	snprintf(buf, sizeof(buf), "%.1f> cm", settings.getNozzleDistance());
        	parentWindow->write(buf, 2, 7);
            break;
        case 3:
            // Enter setting 4
            parentWindow->write("<", 2, 8);
        	snprintf(buf, sizeof(buf), "%d>", settings.getFlowMeterCoefficient());
        	parentWindow->write(buf, 2, 9);
            break;
        case 4:
            // Enter setting 5
            parentWindow->write("<", 2, 5);
        	snprintf(buf, sizeof(buf), "%.1f> L/dk", settings.getMinDosage());
        	parentWindow->write(buf, 2, 6);
            break;
        case 5:
            // Enter setting 6
            parentWindow->write("<", 2, 5);
        	snprintf(buf, sizeof(buf), "%.1f> L/dk", settings.getMaxDosage());
        	parentWindow->write(buf, 2, 6);
            break;
        case 6:
            // Enter setting 7
            parentWindow->write("<", 2, 7);
        	snprintf(buf, sizeof(buf), "%%%.1f>", settings.getMaxDosageVariationPercent());
        	parentWindow->write(buf, 2, 8);
            break;
        case 7:
            // Enter setting 8
            parentWindow->write("<", 2, 7);
        	snprintf(buf, sizeof(buf), "%.1f> L", settings.getTankCapacity());
        	parentWindow->write(buf, 2, 8);
            break;
        case 8:
            // Enter setting 9
            if(settings.getSpeedSource() == Settings::GPS)
                parentWindow->write(">", 2, 2);
            else
                parentWindow->write(">", 2, 8);;
            parentWindow->write("GPS", 2, 3);
        	parentWindow->write("SIMULASYON", 2, 9);
            break;
        case 9:
            // Enter setting 10
            parentWindow->write("<", 2, 5);
        	snprintf(buf, sizeof(buf), "%.1f km/h>", settings.getSimulationSpeed());
        	parentWindow->write(buf, 2, 6);
            break;
        default:
            break;
    }
    parentWindow->showWindow();
}


void SettingsPage::handleButtonInput(ButtonQueueEvent event) {
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
                        return;
                    }
                    inSubMenu = true;
                    enterSetting();
                    break;
                case ButtonEventType::HELD:
                    // Navigate back to main page
                    if (!inSubMenu){
                        selectedItem = 0;
                        rollOverCount = 0;
                        settings.writePageFlash();
                        parentWindow->prevPage();
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
}

void SettingsPage::subMenuMinus(){
    switch (selectedItem) {
        char buf[20];
        case 0:
            // Enter setting 1
            parentWindow->write("Turkce", 2, 2);
            parentWindow->write("English", 2, 11);
            break;
        case 1:
            // Enter setting 2
            parentWindow->write("         ",  2, 8);
            parentWindow->write("<", 2, 8);
            settings.setNozzleCount(settings.getNozzleCount()-1);
        	snprintf(buf, sizeof(buf), "%d>", settings.getNozzleCount());
        	parentWindow->write(buf, 2, 9);
            break;
        case 2:
            // Enter setting 3
            parentWindow->write("         ",  2, 6);
            parentWindow->write("<", 2, 6);
            settings.setNozzleDistance(settings.getNozzleDistance()-0.1f);
        	snprintf(buf, sizeof(buf), "%.1f> cm", settings.getNozzleDistance());
        	parentWindow->write(buf, 2, 7);
            break;
        case 3:
            // Enter setting 4
            parentWindow->write("         ",  2, 8);
            parentWindow->write("<", 2, 8);
            settings.setFlowMeterCoefficient(settings.getFlowMeterCoefficient()-1);
        	snprintf(buf, sizeof(buf), "%d>", settings.getFlowMeterCoefficient());
        	parentWindow->write(buf, 2, 9);
            break;
        case 4:
            // Enter setting 5
            parentWindow->write("           ",  2, 5);
            parentWindow->write("<", 2, 5);
            settings.setMinDosage(settings.getMinDosage()-0.1);
        	snprintf(buf, sizeof(buf), "%.1f> L/dk", settings.getMinDosage());
        	parentWindow->write(buf, 2, 6);
            break;
        case 5:
            // Enter setting 6
            parentWindow->write("           ",  2, 5);
            parentWindow->write("<", 2, 5);
            settings.setMaxDosage(settings.getMaxDosage()-0.1);
        	snprintf(buf, sizeof(buf), "%.1f> L/dk", settings.getMaxDosage());
        	parentWindow->write(buf, 2, 6);
            break;
        case 6:
            // Enter setting 7
            parentWindow->write("         ",  2, 7);
            parentWindow->write("<", 2, 7);
            settings.setMaxDosageVariationPercent(settings.getMaxDosageVariationPercent()-10.0);
        	snprintf(buf, sizeof(buf), "%%%.1f>", settings.getMaxDosageVariationPercent());
        	parentWindow->write(buf, 2, 8);
            break;
        case 7:
            // Enter setting 8
            parentWindow->write("         ",  2, 7);
            parentWindow->write("<", 2, 7);
            settings.setTankCapacity(settings.getTankCapacity()-100.0);
        	snprintf(buf, sizeof(buf), "%.1f> L", settings.getTankCapacity());
        	parentWindow->write(buf, 2, 8);
            break;
        case 8:
            // Enter setting 9
            parentWindow->write(" ", 2, 8);
            parentWindow->write(">", 2, 2);
            settings.setSpeedSource(Settings::GPS);
            break;
        case 9:
            // Enter setting 10
            parentWindow->write("         ",  2, 5);
            parentWindow->write("<", 2, 5);
            settings.setSimulationSpeed(settings.getSimulationSpeed()-0.1);
        	snprintf(buf, sizeof(buf), "%.1f km/h>", settings.getSimulationSpeed());
        	parentWindow->write(buf, 2, 6);
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
            parentWindow->write("Turkce", 2, 2);
            parentWindow->write("English", 2, 11);
            break;
        case 1:
            // Enter setting 2
            parentWindow->write("         ",  2, 8);
            parentWindow->write("<", 2, 8);
            settings.setNozzleCount(settings.getNozzleCount()+1);
        	snprintf(buf, sizeof(buf), "%d>", settings.getNozzleCount());
        	parentWindow->write(buf, 2, 9);
            break;
        case 2:
            // Enter setting 3
            parentWindow->write("         ",  2, 6);
            parentWindow->write("<", 2, 6);
            settings.setNozzleDistance(settings.getNozzleDistance()+0.1f);
        	snprintf(buf, sizeof(buf), "%.1f> cm", settings.getNozzleDistance());
        	parentWindow->write(buf, 2, 7);
            break;
        case 3:
            // Enter setting 4
            parentWindow->write("         ",  2, 8);
            parentWindow->write("<", 2, 8);
            settings.setFlowMeterCoefficient(settings.getFlowMeterCoefficient()+1);
        	snprintf(buf, sizeof(buf), "%d>", settings.getFlowMeterCoefficient());
        	parentWindow->write(buf, 2, 9);
            break;
        case 4:
            // Enter setting 5
            parentWindow->write("           ",  2, 5);
            parentWindow->write("<", 2, 5);
            settings.setMinDosage(settings.getMinDosage()+0.1);
        	snprintf(buf, sizeof(buf), "%.1f> L/dk", settings.getMinDosage());
        	parentWindow->write(buf, 2, 6);
            break;
        case 5:
            // Enter setting 6
            parentWindow->write("           ",  2, 5);
            parentWindow->write("<", 2, 5);
            settings.setMaxDosage(settings.getMaxDosage()+0.1);
        	snprintf(buf, sizeof(buf), "%.1f> L/dk", settings.getMaxDosage());
        	parentWindow->write(buf, 2, 6);
            break;
        case 6:
            // Enter setting 7
            parentWindow->write("         ",  2, 7);
            parentWindow->write("<", 2, 7);
            settings.setMaxDosageVariationPercent(settings.getMaxDosageVariationPercent()+10.0);
        	snprintf(buf, sizeof(buf), "%%%.1f>", settings.getMaxDosageVariationPercent());
        	parentWindow->write(buf, 2, 8);
            break;
        case 7:
            // Enter setting 8
            parentWindow->write("         ",  2, 7);
            parentWindow->write("<", 2, 7);
            settings.setTankCapacity(settings.getTankCapacity()+100.0);
            flowmeter.setTotalVolume(settings.getTankCapacity());
        	snprintf(buf, sizeof(buf), "%.1f> L", settings.getTankCapacity());
        	parentWindow->write(buf, 2, 8);
            break;
        case 8:
            // Enter setting 9
            parentWindow->write(" ", 2, 2);
            parentWindow->write(">", 2, 8);
            settings.setSpeedSource(Settings::SIMULATION);
            break;
        case 9:
            // Enter setting 10
            parentWindow->write("            ",  2, 5);
            parentWindow->write("<", 2, 5);
            settings.setSimulationSpeed(settings.getSimulationSpeed()+0.1);
        	snprintf(buf, sizeof(buf), "%.1f km/h>", settings.getSimulationSpeed());
        	parentWindow->write(buf, 2, 6);
            break;
        default:
            break;
    }
}