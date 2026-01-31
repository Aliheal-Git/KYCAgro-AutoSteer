// File: IValveContoller.hpp
// Path: App\Interfaces\IValveContoller.hpp
// Created by Alican on 2026-01-31

#ifndef APP_INTERFACES_IVALVECONTOLLER_HPP_
#define APP_INTERFACES_IVALVECONTOLLER_HPP_

#include "IValve.hpp"

namespace App::Interfaces::ValveControllerInterface {

    class IValveController {
        public:
            virtual ~IValveController() {}
            virtual void init() = 0;
            virtual void enable() = 0;
            virtual void disable() = 0;

            virtual void setMode(ValveControllerMode newMode) = 0;
            virtual void setValveState(uint8_t valveIndex, ValveState state) = 0;
    };

} // namespace App::Interfaces::ValveControllerInterface

#endif // APP_INTERFACES_IVALVECONTOLLER_HPP_