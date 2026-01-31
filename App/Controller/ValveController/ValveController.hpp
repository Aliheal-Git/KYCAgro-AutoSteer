// File: ValveController.hpp
// Path: App\Controller\ValveController\ValveController.hpp
// Created by Alican on 2026-01-31

#ifndef APP_CONTROLLER_VALVECONTROLLER_VALVECONTROLLER_HPP_
#define APP_CONTROLLER_VALVECONTROLLER_VALVECONTROLLER_HPP_

#include "ControllerCommon.hpp"
#include "IValve.hpp"
#include "ValveCommon.hpp"

using namespace App::Domain::ControllerCommon;
using namespace App::Interfaces::ValveInterface;

namespace App::Controller::ValveController {

    class ValveController {
        public:
            ValveController();
            void init();
            void enable();
            void disable();

            void setMode(ValveControllerMode newMode);
            ValveState getState(uint8_t valveIndex) const;

        private:
            bool enabled = false;
            ValveControllerMode mode = ValveControllerMode::MANUAL;
            IValve* mainValve;
            IValve* nozzleValves[8];
            uint8_t nozzleValveCount = 0;
    };

} // namespace App::Controller::ValveController

#endif // APP_CONTROLLER_VALVECONTROLLER_VALVECONTROLLER_HPP_