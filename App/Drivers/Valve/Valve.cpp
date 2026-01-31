#include "Valve.hpp"
#include "ValveCommon.hpp"
#include <math.h>

using namespace App::Drivers::Valve;
using namespace App::Domain::ValveCommon;

Valve::Valve(GPIO_TypeDef* OpenPort, uint16_t OpenPin, GPIO_TypeDef* ClosePort, uint16_t ClosePin)
    : openPort(OpenPort), openPin(OpenPin), closePort(ClosePort), closePin(ClosePin),
      autoStatus(ValveStatus::CLOSED), manualStatus(ValveStatus::CLOSED), currentMode(ValveMode::AUTO) {
    // Initialize GPIO pins
    HAL_GPIO_WritePin(openPort, openPin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(closePort, closePin, GPIO_PIN_RESET);
}

Valve::~Valve() {
    // Ensure valve is closed on destruction
    HAL_GPIO_WritePin(openPort, openPin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(closePort, closePin, GPIO_PIN_RESET);
}

void Valve::open(ValveMode mode) {
    currentMode == ValveMode::AUTO ? autoStatus = ValveStatus::OPEN : manualStatus = ValveStatus::OPEN;
    if (currentMode == mode){
        HAL_GPIO_WritePin(openPort, openPin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(closePort, closePin, GPIO_PIN_RESET);
    }
}

void Valve::close(ValveMode mode) {
    mode == ValveMode::AUTO ? autoStatus = ValveStatus::CLOSED : manualStatus = ValveStatus::CLOSED;
    if (currentMode == mode){
        HAL_GPIO_WritePin(openPort, openPin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(closePort, closePin, GPIO_PIN_SET);
    }
}

void Valve::setMode(ValveMode mode) {
    currentMode = mode;
    if (currentMode == ValveMode::AUTO) {
        if (autoStatus == ValveStatus::OPEN) {
            open(currentMode);
        } else {
            close(currentMode);
        }
    } else {
        if (manualStatus == ValveStatus::OPEN) {
            open(currentMode);
        } else {
            close(currentMode);
        }
    }
}

ValveMode Valve::getMode() const {
    return currentMode;
}

ValveStatus Valve::getStatus() const {
    return (currentMode == ValveMode::AUTO) ? autoStatus : manualStatus;
}

ProportionalValve::ProportionalValve(TIM_HandleTypeDef* PwmOnTimer, uint32_t PwmOnChannel, TIM_HandleTypeDef* PwmOffTimer, uint32_t PwmOffChannel)
    : pwmOnTimer(PwmOnTimer), pwmOnChannel(PwmOnChannel), pwmOffTimer(PwmOffTimer), pwmOffChannel(PwmOffChannel),
      dutyCycle(0.0f) {
    
    __HAL_TIM_SET_COMPARE(pwmOnTimer, pwmOnChannel, 0);
    __HAL_TIM_SET_COMPARE(pwmOffTimer, pwmOffChannel, 0);
    HAL_TIM_PWM_Start(pwmOnTimer, pwmOnChannel);
    HAL_TIM_PWM_Start(pwmOffTimer, pwmOffChannel);
}

ProportionalValve::~ProportionalValve() {
    HAL_TIM_PWM_Stop(pwmOnTimer, pwmOnChannel);
    HAL_TIM_PWM_Stop(pwmOffTimer, pwmOffChannel);
}

void ProportionalValve::setDutyCycle(float dutyCycle) {
    if (dutyCycle < -1.0f) dutyCycle = -1.0f;
    if (dutyCycle > 1.0f) dutyCycle = 1.0f;
    this->dutyCycle = coefDutyCycle*dutyCycle;
    if (dutyCycle > 0) {
        uint32_t pulse = static_cast<uint32_t>(dutyCycle * (__HAL_TIM_GET_AUTORELOAD(pwmOffTimer)));
        __HAL_TIM_SET_COMPARE(pwmOnTimer, pwmOnChannel, pulse);
        __HAL_TIM_SET_COMPARE(pwmOffTimer, pwmOffChannel, 0);
    } else if (dutyCycle < 0) {
        uint32_t pulse = static_cast<uint32_t>(- dutyCycle * (__HAL_TIM_GET_AUTORELOAD(pwmOffTimer)));
        __HAL_TIM_SET_COMPARE(pwmOnTimer, pwmOnChannel, 0);
        __HAL_TIM_SET_COMPARE(pwmOffTimer, pwmOffChannel, pulse);
    } else {
        __HAL_TIM_SET_COMPARE(pwmOnTimer, pwmOnChannel, 0);
        __HAL_TIM_SET_COMPARE(pwmOffTimer, pwmOffChannel, 0);
    }
}
