// File: IValveController.hpp
// Path: App\Interfaces\IValveController.hpp
// Created by Alican on 2026-01-31

#ifndef APP_INTERFACES_IVALVECONTROLLER_HPP_
#define APP_INTERFACES_IVALVECONTROLLER_HPP_

#include "ControllerCommon.hpp"
#include "IValve.hpp"
#include "ValveCommon.hpp"

using namespace App::Domain;

namespace App::Interfaces {

    class IValveController {
        public:
            virtual ~IValveController() = default;
            virtual ValveState getValveState(uint8_t valveIndex) const = 0;
            virtual ValveControllerMode getMode() const = 0;
            virtual void setNozzleValveCount(uint8_t count) = 0;
    };

} // namespace App::Interfaces

#endif // APP_INTERFACES_IVALVECONTROLLER_HPP_

