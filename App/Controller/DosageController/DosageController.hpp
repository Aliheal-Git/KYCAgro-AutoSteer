// File: DosageController.hpp
// Path: App\Controller\DosageController.hpp
// Created by Alican on 2026-01-31

#ifndef APP_CONTROLLER_DOSAGECONTROLLER_HPP_
#define APP_CONTROLLER_DOSAGECONTROLLER_HPP_

#include "PID.h"
#include "IDosageController.hpp"
#include "IGPS.hpp"
#include "IFlowmeter.hpp"
#include "IValve.hpp"
#include "SettingsCommon.hpp"
#include "IButton.hpp"

using namespace App::Interfaces;
using namespace App::Domain;
namespace App::Controller {

class DosageController : public IDosageController, public IButtonEventListener {
	public:
		DosageController(float P, float I, float D, Settings* Settings, IGPS* gpsDevice, IFlowmeter* flowmeterDevice, IValve* propValveDevice);
		void init();
		DosageControllerTaskResult tick() override;
		void enable() override;
		void disable() override;
		void setTargetDosage(float dosage);
		
		float getTargetDosage() const override { return targetDosage; }
		float getDosage() const override { return currentDosage; }
		DosageControllerMode getMode() const override {
		    return mode;
		}
		void onButtonEvent(const ButtonQueueEvent& queueEvent) override;
	private: 
		PIDController<float> pidController;
		Settings* settings;
		IGPS* gps;
		IFlowmeter* flowmeter;
		IValve* proportionalValve;
		float currentDosage = 0;
		float targetDosage = 0;
		bool enabled = false;
		DosageControllerMode mode = DosageControllerMode::MANUAL;

	    float calculateDosage();
};

} // namespace App::Controller

#endif // APP_CONTROLLER_DOSAGECONTROLLER_HPP_


