// File: IFlowmeter.hpp
// Path: App\Interfaces\IFlowmeter.hpp
// Created by Alican on 2026-01-20

#ifndef APP_INTERFACES_IFLOWMETER_HPP_
#define APP_INTERFACES_IFLOWMETER_HPP_

namespace App::Interfaces {

/**
 * @brief Interface for flowmeter operations.
 */
class IFlowmeter {
public:
    /**
     * @brief Returns flow rate in liters per minute    
     */
    virtual float getFlowRate() const = 0; // Returns flow rate in liters per minute
    /**
     * @brief Returns total volume in liters
     */
    virtual float getVolume() const = 0; // Returns total volume in liters
    /**
     * @brief Handle timer overflow event
     * @result Increments overflow counter
     */
    virtual void onTimerOverflow() = 0;
    /**
     * @brief Capture the time when a pulse is detected
     * @param time The current captured time
     * @result Updates pulse width and calculates flow
     */
    virtual void onPulse(uint32_t time) = 0;
    virtual ~IFlowmeter() = default;
};
} // namespace App::Interfaces

#endif // APP_INTERFACES_IFLOWMETER_HPP_