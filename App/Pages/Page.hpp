// File: Page.hpp
// Path: App\Pages\Page.hpp
// Created by Alican on 2026-01-24

#ifndef APP_PAGES_PAGE_HPP_
#define APP_PAGES_PAGE_HPP_

#include "IPage.hpp"
#include "IWindow.hpp"
#include "WindowCommon.hpp"
#include "SettingsCommon.hpp"


using namespace App::Interfaces::WindowInterface;
using namespace App::Interfaces::PageInterface;
using namespace App::Domain::SettingsCommon;

class WelcomePage : public IPage {
	public:
		WelcomePage(IWindow* win) : IPage(win) {}
		PageFuncResult render() override;
		PageFuncResult handleButtonInput(ButtonQueueEvent event) override {
			return {PageNavRequest::NONE, 0};
		}
		bool task(void) override {
			return false;
		}
};

class MainPage : public IPage {
	public:
		explicit MainPage(IWindow* win, Settings& params) : IPage(win), settings(params) {}
		PageFuncResult render() override;
		PageFuncResult task(void) override;
		PageFuncResult handleButtonInput(ButtonQueueEvent event) override;
	private:
		Settings& settings;
		float speed = 0;
		float targetDosage = 0;
		float dosage = 0;
		float dosageSum = 0;
		const uint8_t dosageSampleCount = 20;

		void setSpeed(float speed);
		void setDosage(float dosage);
		void setTargetDosage(float target_dosage);
		void setValveOn(uint8_t valveIndex);
		void setValveOff(uint8_t valveIndex);
		void setDosageModeAuto();
		void setDosageModeManual();
		void setGPSAuto();
		void setGPSManual();
		void setSelectedProgram();


		

};

class SettingsPage : public IPage {
	public:
		SettingsPage(IWindow* win) : IPage(win) {}

		void render() override;
		void handleButtonInput(ButtonQueueEvent event) override;

	private:
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
		ProgramsPage(IWindow* win) : IPage(win) {}

		void render() override;
		void handleButtonInput(ButtonQueueEvent event) override;
	private:
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
		InformationPage(IWindow* win) : IPage(win) {}

		void render() override;
		void handleButtonInput(ButtonQueueEvent event) override;
	private:
		bool task(void) override;
		void updateCapacity();
		void updateFlow();
};

#endif // APP_PAGES_PAGE_HPP_

