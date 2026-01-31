#ifndef VALVE_HPP
#define VALVE_HPP

#include "ValveCommon.hpp"
#include "gpio.h"
#include "tim.h"

#include "IValve.hpp"

using namespace App::Interfaces;

namespace App::Drivers {
class Valve : public IValve {
public:
    Valve(GPIO_TypeDef* OpenPort, uint16_t OpenPin, GPIO_TypeDef* ClosePort, uint16_t ClosePin);
    ~Valve();
    void setMode(ValveMode mode) override;
    ValveMode getMode() const override;
    ValveState getStatus() const override;
    void open(ValveMode mode) override;
    void close(ValveMode mode) override;
    void setDutyCycle(float dutyCycle) override {}; // Not applicable for on/off valves

private:
    GPIO_TypeDef* openPort;
    uint16_t openPin;

    GPIO_TypeDef* closePort;
    uint16_t closePin;

    ValveState autoStatus = ValveState::CLOSED;
    ValveState manualStatus = ValveState::CLOSED;
    ValveMode currentMode = ValveMode::MANUAL;

};

class ProportionalValve : public IValve {
    public:
        ProportionalValve(TIM_HandleTypeDef* pwmOnTimer, uint32_t pwmOnChannel, TIM_HandleTypeDef* pwmOffTimer, uint32_t pwmOffChannel);
        ~ProportionalValve();

        ValveMode getMode() const override { return ValveMode::AUTO; }; // Proportional valves are always in AUTO mode
        void setMode(ValveMode mode) override {};
        ValveState getStatus() const override { return (dutyCycle > 0.01f) ? ValveState::OPEN : ValveState::CLOSED; };
        void open(ValveMode mode) override {};
        void close(ValveMode mode) override {};
        void setDutyCycle(float dutyCycle) override; // -1.0 to 1.0
    private:
        TIM_HandleTypeDef* pwmOnTimer;
        uint32_t pwmOnChannel;
        TIM_HandleTypeDef* pwmOffTimer;
        uint32_t pwmOffChannel;
        float coefDutyCycle = 0.6;
        float dutyCycle = 0.0f; // -1.0 to 1.0
        float limit;
    };
} // namespace App

#endif // VALVE_HPP
