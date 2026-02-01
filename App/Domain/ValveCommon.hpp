// File: ValveCommon.hpp
// Path: App\Domain\ValveCommon.hpp
// Created by Alican on 2026-01-24

#ifndef APP_DOMAIN_VALVECOMMON_HPP_
#define APP_DOMAIN_VALVECOMMON_HPP_

namespace App::Domain {
    enum class ValveMode : bool {
        AUTO,
        MANUAL
    };
    enum class ValveState : bool {
        OPEN = true,
        CLOSED = false
    };
} // namespace App::Domain

#endif // APP_DOMAIN_VALVECOMMON_HPP_