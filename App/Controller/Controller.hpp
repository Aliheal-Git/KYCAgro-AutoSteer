/*
 * Controller.hpp
 *
 *  Created on: Sep 2, 2025
 *      Author: alica
 */

#ifndef CONTROLLER_CONTROLLER_HPP_
#define CONTROLLER_CONTROLLER_HPP_

#include "PID.h"
#include "cmsis_os.h"

class Controller{
	public:
		enum Mode {
			AUTO,
			MANUAL
		};
		const uint8_t maxValve = 5;

		Controller();
		void init();
		void enablePIDController();
		void disablePIDController();
		void setSpeed(const float speed);
		float getSpeed() const { return _speed;};
		void setTargetDosage(float dosage);
		float getTargetDosage() const { return _targetDosage; }
		void calculateDosage();
		float getDosage() const { return _currentDosage; }
		void setMode(Mode m);
		Mode getMode() const;

	private:
		PIDController<float> pidController;
		float _currentDosage = 0;
		float _targetDosage = 0;
		float _speed = 0;
		Mode _mode = MANUAL;

		TaskHandle_t taskHandle;

	    // static wrapper function
	    static void taskEntryPoint(void *pvParameters) {
	        // recover the object pointer
	        Controller *self = static_cast<Controller*>(pvParameters);
	        self->task();
	    }

	    // static wrapper function
	    static void pidTaskEntryPoint(void *pvParameters) {
	        // recover the object pointer
	        Controller *self = static_cast<Controller*>(pvParameters);
	        self->pidTask();
	    }

	    void task();
	    void pidTask();
		void dosageCalculation();
};

extern Controller controller;





#endif /* CONTROLLER_CONTROLLER_HPP_ */
