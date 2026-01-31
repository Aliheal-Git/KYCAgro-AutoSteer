// File: IGPS.hpp
// Path: App\Interfaces\IGPS.hpp
// Created by Alican on 2026-01-25

#ifndef APP_INTERFACES_IGPS_HPP_
#define APP_INTERFACES_IGPS_HPP_

#include <cstdint>

namespace App::Interfaces::GPSInterface {

class IGPS {
    public:
        virtual ~IGPS() = default;
        virtual float getSpeed() const = 0;
        virtual bool getValveStatus(uint8_t valveIndex) const = 0;
};

} // namespace App::Interfaces::GPSInterface

#endif // APP_INTERFACES_IGPS_HPP_