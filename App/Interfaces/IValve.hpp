// File: IValve.hpp
// Path: App\Interfaces\IValve.hpp
// Created by Alican on 2026-01-29

#ifndef APP_INTERFACES_IVALVE_HPP_
#define APP_INTERFACES_IVALVE_HPP_

#include "ValveCommon.hpp"

using namespace App::Domain::ValveCommon;

namespace App::Interfaces::ValveInterface {
    
/**
    * @brief Interface for Valve operations.
 */
class IValve {
    public:
        virtual ~IValve() = default;    
        /**
         * @brief Set the mode of the valve.
         * @param mode The mode to set.
         */
        virtual void setMode(ValveMode mode) = 0;
        /**
         * @brief Get the current mode of the valve.
         * @return The current mode.
         */
        virtual ValveMode getMode() const = 0;
        /**
         * @brief Open the valve in the specified mode.
         * @param mode The mode in which to open the valve.
         */
        virtual void open(ValveMode mode) = 0;
        /**
         * @brief Close the valve in the specified mode.
         * @param mode The mode in which to close the valve.
         */
        virtual void close(ValveMode mode) = 0;
        /**
         * @brief Get the current status of the valve.
         * @return The current status.
         */
        virtual ValveStatus getStatus() const = 0;
        /**
         * @brief Set the duty cycle for proportional valves.
         * @param dutyCycle The duty cycle to set (-1.0 to 1.0).
         */
        virtual void setDutyCycle(float dutyCycle) = 0;
};

} // namespace App::Interfaces::ValveInterface

#endif // APP_INTERFACES_IVALVE_HPP_