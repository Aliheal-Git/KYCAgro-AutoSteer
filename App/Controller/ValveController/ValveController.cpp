#include "ValveController.hpp"
#include "ButtonCommon.hpp"
#include "ValveCommon.hpp"

using namespace App::Controller;

ValveController::ValveController() {
    // Constructor implementation (if needed)
}

void ValveController::init(IValve* mainValvePtr, IValve* nozzleValvesArray[], uint8_t nozzleValveCnt) {
    mainValve = mainValvePtr;
    mainValve->setMode(ValveMode::AUTO);
    nozzleValveCount = nozzleValveCnt > MAX_NOZZLE_VALVES ? MAX_NOZZLE_VALVES : nozzleValveCnt;
    for (uint8_t i = 0; i < nozzleValveCount; ++i) {
        nozzleValves[i] = nozzleValvesArray[i];
    }
    enabled = true;
}

void ValveController::enable() {
    enabled = true;
    if (activeNozzleValveCount > 0) {
        mainValve->open(ValveMode::AUTO);
    }
}

void ValveController::disable() {
    enabled = false;
    mainValve->close(ValveMode::AUTO);
}

void ValveController::setNozzleValveCount(uint8_t count) {
    nozzleValveCount = count > MAX_NOZZLE_VALVES ? MAX_NOZZLE_VALVES : count;
}

void ValveController::setMode(ValveControllerMode newMode) {
    mode = newMode;
    if (mode == ValveControllerMode::MANUAL) {
        mainValve->setMode(ValveMode::MANUAL);
        for (uint8_t i = 0; i < nozzleValveCount; ++i) {
            nozzleValves[i]->setMode(ValveMode::MANUAL);
        }
    } else {
        for (uint8_t i = 0; i < nozzleValveCount; ++i) {
            nozzleValves[i]->setMode(ValveMode::AUTO);
        }
    }
}

ValveControllerTaskResult ValveController::task() {
    if (mode == ValveControllerMode::GPS) {
        for (uint8_t i = 0; i < nozzleValveCount; ++i) {
            if (gps->getValveState(i)) {
                if (nozzleValves[i]->getStatus() == ValveState::CLOSED) {
                    if (activeNozzleValveCount < nozzleValveCount) {
                        activeNozzleValveCount++;
                    }
                    if (activeNozzleValveCount == 1) {
                        mainValve->open(ValveMode::AUTO);
                    }
                    nozzleValves[i]->open(ValveMode::AUTO);
                }
            } else if (nozzleValves[i]->getStatus() == ValveState::OPEN) {
                nozzleValves[i]->close(ValveMode::AUTO);
                if (activeNozzleValveCount > 0) {
                    activeNozzleValveCount--;
                    if (activeNozzleValveCount == 0) {
                        mainValve->close(ValveMode::AUTO);
                    }
                }
            }
        }
    }

    return {true, 100}; // Executed, check again in 500 ms
}

void ValveController::onButtonEvent(const ButtonQueueEvent& queueEvent) {
    if (queueEvent.buttonType == ButtonType::MAIN) {
        if (queueEvent.eventType == ButtonEventType::PRESSED) {
            if (activeNozzleValveCount > 0) {
                mainValve->open(ValveMode::AUTO);
            } 
        } else if (queueEvent.eventType == ButtonEventType::RELEASED) {
            mainValve->close(ValveMode::AUTO);
        }
        return;
    }
    for (uint8_t i = static_cast<uint8_t>(ButtonType::VALVE1); i <= static_cast<uint8_t>(ButtonType::VALVE1) + nozzleValveCount - 1; ++i) {
        if (queueEvent.buttonType == static_cast<ButtonType>(i)) {
            if (queueEvent.eventType == ButtonEventType::PRESSED) {
                nozzleValves[i - static_cast<uint8_t>(ButtonType::VALVE1)]->open(ValveMode::MANUAL);
                activeNozzleValveCount++;
                if (activeNozzleValveCount == 1) {
                    mainValve->open(ValveMode::AUTO);
                }
                return;
            } else if (queueEvent.eventType == ButtonEventType::RELEASED) {
                nozzleValves[i - static_cast<uint8_t>(ButtonType::VALVE1)]->close(ValveMode::MANUAL);
                if (activeNozzleValveCount > 0) {
                    activeNozzleValveCount--;
                    if (activeNozzleValveCount == 0) {
                        mainValve->close(ValveMode::AUTO);
                    }
                }
                return;
            }
        }
    }
}