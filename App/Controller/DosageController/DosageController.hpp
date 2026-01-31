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

using namespace App::Interfaces::GPSInterface;
using namespace App::Interfaces::FlowmeterInterface;
using namespace App::Interfaces::ValveInterface;
using namespace App::Domain::SettingsCommon;
using namespace App::Interfaces::DosageControllerInterface;

namespace App::Controller::DosageController {

class DosageController : public IDosageController {
	public:
		DosageController(float P, float I, float D, Settings* Settings, IGPS* gpsDevice, IFlowmeter* flowmeterDevice, IValve* propValveDevice);
		void init();
		DosageControllerTaskResult tick() override;
		void enable() override;
		void disable() override;
		void setTargetDosage(float dosage) override;
		float getTargetDosage() const override { return targetDosage; }
	private: 
		PIDController<float> pidController;
		Settings* settings;
		IGPS* gps;
		IFlowmeter* flowmeter;
		IValve* proportionalValve;
		float currentDosage = 0;
		float targetDosage = 0;
		bool enabled = false;

	    float calculateDosage();
};

} // namespace App::Controller::DosageController

#endif // APP_CONTROLLER_DOSAGECONTROLLER_HPP_


