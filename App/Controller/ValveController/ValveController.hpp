// File: ValveController.hpp
// Path: App\Controller\ValveController\ValveController.hpp
// Created by Alican on 2026-01-31

#ifndef APP_CONTROLLER_VALVECONTROLLER_VALVECONTROLLER_HPP_
#define APP_CONTROLLER_VALVECONTROLLER_VALVECONTROLLER_HPP_

#include "ButtonCommon.hpp"
#include "ButtonService.hpp"
#include "ControllerCommon.hpp"
#include "IButton.hpp"
#include "IValve.hpp"
#include "ValveCommon.hpp"
#include "IGPS.hpp"

#define MAX_NOZZLE_VALVES 8

using namespace App::Domain;
using namespace App::Interfaces;

namespace App::Controller::ValveController {
    struct ValveControllerTaskResult {
        bool executed;
        uint32_t nextTickDelayMs;
    };
    class ValveController : public IButtonEventListener{
        public:
            ValveController();
            void init(IValve* mainValvePtr, IValve* nozzleValvesArray[], uint8_t nozzleValveCnt);
            void enable();
            void disable();

            void setValveState(uint8_t valveIndex, ValveState state, ValveMode mode);
            void setMode(ValveControllerMode newMode);
            ValveState getState(uint8_t valveIndex) const;
            ValveControllerTaskResult task();

            void onButtonEvent(const ButtonQueueEvent& queueEvent) override;

        private:
            bool enabled = false;
            ValveControllerMode mode = ValveControllerMode::MANUAL;
            IValve* mainValve;
            IValve* nozzleValves[MAX_NOZZLE_VALVES];
            uint8_t nozzleValveCount = 0;
            uint8_t activeNozzleValveCount = 0;
            IGPS* gps;
    };

} // namespace App::Controller::ValveController

#endif // APP_CONTROLLER_VALVECONTROLLER_VALVECONTROLLER_HPP_