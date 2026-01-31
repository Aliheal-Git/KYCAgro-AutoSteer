// File: ControllerCommon.hpp
// Path: App\Domain\ControllerCommon.hpp
// Created by Alican on 2026-01-25

#ifndef APP_DOMAIN_CONTROLLERCOMMON_HPP_
#define APP_DOMAIN_CONTROLLERCOMMON_HPP_

namespace App::Domain::ControllerCommon {

    /**
     * @brief Enumeration for controller modes.
     * AUTO: Automatic mode.
     * MANUAL: Manual mode.
     */
    enum class ControllerMode : uint8_t {
        AUTO = 0,
        MANUAL = 1
    };
    

#endif // APP_DOMAIN_CONTROLLERCOMMON_HPP_