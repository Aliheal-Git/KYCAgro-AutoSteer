// File: ControllerCommon.hpp
// Path: App\Domain\ControllerCommon.hpp
// Created by Alican on 2026-01-25

#ifndef APP_DOMAIN_CONTROLLERCOMMON_HPP_
#define APP_DOMAIN_CONTROLLERCOMMON_HPP_

#include <cstdint>

namespace App::Domain::ControllerCommon {

    /**
     * @brief Enumeration for controller modes.
     * AUTO: Automatic mode.
     * MANUAL: Manual mode.
     */
    enum class DosageControllerMode : uint8_t {
        MANUAL = 0,
        AUTO = 1
    };
    
    /**
     * @brief Enumeration for valve controller modes.
     * MANUAL: Manual mode.
     * GPS: GPS-based mode.
     */
    enum class ValveControllerMode : uint8_t {
        MANUAL = 0,
        GPS = 1
    };

} // namespace App::Domain::ControllerCommon

#endif // APP_DOMAIN_CONTROLLERCOMMON_HPP_