// File: Page.hpp
// Path: App\Pages\Page.hpp
// Created by Alican on 2026-01-24

#ifndef APP_PAGES_PAGE_HPP_
#define APP_PAGES_PAGE_HPP_

#include "IDosageController.hpp"
#include "IFlowmeter.hpp"
#include "IPage.hpp"
#include "IFlash.hpp"
#include "IValveController.hpp"
#include "IGPS.hpp"


#include "IWindow.hpp"
#include "WindowCommon.hpp"
#include "SettingsCommon.hpp"

using namespace App::Interfaces;
using namespace App::Domain;

namespace App::Pages {

class WelcomePage : public IPage {
	public:
		WelcomePage(IWindow* win) : IPage(win) {}
		PageFuncResult render() override;
		PageFuncResult handleButtonInput(ButtonQueueEvent event) override {
			return {PageNavRequest::NONE, 0};
		}
		PageFuncResult update(void) override {
			return {PageNavRequest::NONE, 0};
		}
};

class MainPage : public IPage {
	public:
		explicit MainPage(IWindow* win, Settings& params, IFlash* Flash, 
			IDosageController* DosageController, IValveController* ValveController) 
			: IPage(win), settings(params), flash(Flash), dosageController(DosageController), valveController(ValveController) {}
		PageFuncResult render() override;
		PageFuncResult update() override;
		PageFuncResult handleButtonInput(ButtonQueueEvent event) override;
	private:
		Settings& settings;
		IFlash* flash;
		IDosageController* dosageController;
		IValveController* valveController;
		IGPS* gpsDevice;

		bool uiValveStates[8] = {false, false, false, false, false, false, false, false};
		float uiSpeed = 0;
		float uiDosage = 0;
		float uiTargetDosage = 0;
		float dosageSum = 0;
		const uint8_t dosageSampleCount = 10;

		void setUISpeed(float speed);
		void setUIDosage(float dosage);
		void setTargetDosage(float target_dosage);
		void setUIValveOn(uint8_t valveIndex);
		void setUIValveOff(uint8_t valveIndex);
		void setDosageModeAuto();
		void setDosageModeManual();
		void setGPSAuto();
		void setGPSManual();
		void setSelectedProgram();


		

};

class SettingsPage : public IPage {
	public:
		SettingsPage(IWindow* win, Settings* settings, IFlowmeter* flowmeter, IFlash* flash) 
			: IPage(win), settings(settings), flowmeter(flowmeter), flash(flash) {}

		PageFuncResult render() override;
		PageFuncResult handleButtonInput(ButtonQueueEvent event) override;

	private:
		Settings* settings;
		IFlowmeter* flowmeter;
		IFlash* flash;
		uint8_t selectedItem = 0;
		uint8_t rollOverCount = 0;
		bool inSubMenu = false;
		const uint8_t maxVisibleItems = 4;
		const uint8_t itemCount = 10;
		const char* items[12] = {
			"Dil",
			"Nozzle Sayisi",
			"Nozzle Araligi",
			"Debimetre Katsayisi",
			"Minimum Debi",
			"Maksimum Debi",
			"Maksimum Varyasyon",
			"Tank Hacmi",
			"Hiz Kaynagi",
			"Simulasyon Hizi",
			"",
			""
		};


		void updateSelectionIndicatorUp();
		void updateSelectionIndicatorDown();
		void enterSetting();
		void subMenuMinus();
		void subMenuPlus();
};

class ProgramsPage : public IPage {
	public:
		ProgramsPage(IWindow* win, Settings* settings, IFlash* flash) : IPage(win), settings(settings), flash(flash) {}

		PageFuncResult render() override;
		PageFuncResult handleButtonInput(ButtonQueueEvent event) override;
	private:
		Settings* settings;
		IFlash* flash;
		bool inSubMenu = false;
		uint8_t selectedItem = 0;
		uint8_t itemCount = 3;

		void updateSelectionIndicatorUp();
		void updateSelectionIndicatorDown();
		void renderSelectedProgram();
		void enterSetting();
		void subMenuMinus();
		void subMenuPlus();
};

class InformationPage : public IPage {
		public:
		InformationPage(IWindow* win, IFlowmeter* flowmeter) : IPage(win), flowmeter(flowmeter) {}

		PageFuncResult render() override;
		PageFuncResult handleButtonInput(ButtonQueueEvent event) override;
		PageFuncResult update(void) override;
	private:
		void updateCapacity();
		void updateFlow();
        IFlowmeter* flowmeter;
};

} // namespace App::Pages
#endif // APP_PAGES_PAGE_HPP_

