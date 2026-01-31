// File: GPS.hpp
// Path: App\Drivers\GPS\GPS.hpp
// Created by Alican on 2026-01-25

#ifndef APP_DRIVERS_GPS_GPS_HPP_
#define APP_DRIVERS_GPS_GPS_HPP_

#include "IGPS.hpp"

using namespace App::Interfaces::GPSInterface;

#define MAX_VALVE_COUNT 8

class GPS : public IGPS {
    private: 
        float speed = 0.0f;
        bool valveStatus[MAX_VALVE_COUNT] = {false};
    public:
        GPS();

        float getSpeed() const override {
            return speed;
        }

        bool getValveStatus(uint8_t valveIndex) const override {
            if (valveIndex >= MAX_VALVE_COUNT) {
                return false; // Invalid index
            }
            return valveStatus[valveIndex];
        }

        void receiveGPSData();
};

#endif // APP_DRIVERS_GPS_GPS_HPP_