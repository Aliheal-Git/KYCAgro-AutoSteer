// File: SettingsCommon.hpp
// Path: App\Domain\SettingsCommon.hpp
// Created by Alican on 2026-01-24

#ifndef APP_DOMAIN_SETTINGSCOMMON_HPP_
#define APP_DOMAIN_SETTINGSCOMMON_HPP_

#include "string.h"
#include <cstdint>

namespace App::Domain {

    /**
     * @brief Enumeration for speed source options.
     * GPS: Speed is obtained from GPS data.
     * SIMULATION: Speed is simulated within the system.
     */
    enum class SPEED_SOURCE : bool {
        GPS = 0,
        SIMULATION = 1
    };

    /**
     * @brief Enumeration for nozzle types.
     * ISO01: ISO standard nozzle with 0.1 diameter.
     * ISO015: ISO standard nozzle with 0.15 diameter.
     * ISO02: ISO standard nozzle with 0.2 diameter.
     * ISO025: ISO standard nozzle with 0.25 diameter.
     * ISO03: ISO standard nozzle with 0.3 diameter.
     * ISO04: ISO standard nozzle with 0.4 diameter.
     * ISO05: ISO standard nozzle with 0.5 diameter.
     * ISO06: ISO standard nozzle with 0.6 diameter.
     * BRASS01: Brass nozzle with 0.1 diameter.
     * BRASS012: Brass nozzle with 0.12 diameter.
     * BRASS015: Brass nozzle with 0.15 diameter.
     */
    enum class NOZZLE_TYPE : uint8_t {
        ISO01 = 0,
        ISO015 = 1,
        ISO02 = 2,
        ISO025 = 3,
        ISO03 = 4,
        ISO04 = 5,
        ISO05 = 6,
        ISO06 = 7,
        BRASS01 = 8,
        BRASS012 = 9,
        BRASS015 = 10 
    };

    /**
     * @brief Structure to hold settings parameters.
     * nozzleCount: Number of nozzles.
     * nozzleDistance: Distance between nozzles.
     * flowMeterCoefficient: Coefficient for the flow meter.
     * minDosage: Minimum dosage value.
     * maxDosage: Maximum dosage value.
     * maxDosageVariationPercent: Maximum dosage variation percentage.
     * tankCapacity: Capacity of the tank.
     * speedSource: Source of speed data.
     * simulationSpeed: Speed used in simulation mode.
     * targetDosage: Target dosage value.
     * selectedProgram: Currently selected program.
     * selectedNozzleType: Array of selected nozzle types.
     * dosageValue: Array of target dosage values for each nozzle.
     */
    struct SettingsParameters {
        uint8_t  nozzleCount;
        float    nozzleDistance;
        uint16_t flowMeterCoefficient;
        float    minDosage;
        float    maxDosage;
        float    maxDosageVariationPercent;
        float    tankCapacity;
        SPEED_SOURCE    speedSource;
        float    simulationSpeed;
        float    targetDosage;
        uint8_t  selectedProgram;
        NOZZLE_TYPE  selectedNozzleType[4];
        float    dosageValue[4];
        float    nozzleValveCount;
    };

    /** 
     * @brief Class to manage settings data.
     */
    class Settings {
        private:
            SettingsParameters parameters;
        public:
            /**
             * @brief Get the current settings parameters.
             */
            SettingsParameters getSettingsParameters() const { return parameters; }

            /**
             * @brief Set the settings data from a raw byte array.
             */
            void setSettingsData(uint8_t* newData) { memcpy(&parameters, newData, sizeof(SettingsParameters)); }

            /**
             * @brief Get the raw byte array of settings data.
             */
            uint8_t* getRawData() { return reinterpret_cast<uint8_t*>(&parameters); }

            /**
             * @brief Get the number of nozzles.
             */
            uint8_t getNozzleCount() const { return parameters.nozzleCount; }

            /**
             * @brief Set the number of nozzles.
             */
            void setNozzleCount(uint8_t val) { parameters.nozzleCount = val; }
            
            /** 
             * @brief Get the distance between nozzles.
             */
            float getNozzleDistance() const { return parameters.nozzleDistance; }

            /**
             * @brief Set the distance between nozzles.
             */
            void setNozzleDistance(float val) { parameters.nozzleDistance = val; }

            /**
             * @brief Get the flow meter coefficient.
             */
            uint16_t getFlowMeterCoefficient() const { return parameters.flowMeterCoefficient; }

            /**
             * @brief Set the flow meter coefficient.
             */
            void setFlowMeterCoefficient(uint16_t val) { parameters.flowMeterCoefficient = val; }

            /**
             * @brief Get the minimum dosage.
             */
            float getMinDosage() const { return parameters.minDosage; }

            /**
             * @brief Set the minimum dosage.
             */
            void setMinDosage(float val) { parameters.minDosage = val; }

            /**
             * @brief Get the maximum dosage.
             */
            float getMaxDosage() const { return parameters.maxDosage; }

            /**
             * @brief Set the maximum dosage.
             */
            void setMaxDosage(float val) { parameters.maxDosage = val; }

            /**
             * @brief Get the maximum dosage variation percent.
             */
            float getMaxDosageVariationPercent() const { return parameters.maxDosageVariationPercent; }
            
            /**
             * @brief Set the maximum dosage variation percent.
             */
            void setMaxDosageVariationPercent(float val) { parameters.maxDosageVariationPercent = val; }

            /**
             * @brief Get the tank capacity.
             */
            float getTankCapacity() const { return parameters.tankCapacity; }

            /**
             * @brief Set the tank capacity.
             */
            void setTankCapacity(float val) { parameters.tankCapacity = val; }

            /**
             * @brief Get the speed source.
             */
            SPEED_SOURCE getSpeedSource() const { return parameters.speedSource; }

            /**
             * @brief Set the speed source.
             */
            void setSpeedSource(SPEED_SOURCE val) { parameters.speedSource = val; }

            /**
             * @brief Get the simulation speed.
             */
            float getSimulationSpeed() const { return parameters.simulationSpeed; }

            /**
             * @brief Set the simulation speed.
             */
            void setSimulationSpeed(float val) { parameters.simulationSpeed = val; }

            /**
             * @brief Get the selected program.
             */
            uint8_t getSelectedProgram() const { return parameters.selectedProgram; }

            /**
             * @brief Set the selected program.
             */
            void setSelectedProgram(uint8_t val) { parameters.selectedProgram = val; }

            /**
             * @brief Get the selected nozzle type for a given index.
             */
            NOZZLE_TYPE getSelectedNozzleType(uint8_t index) const { return parameters.selectedNozzleType[index]; }

            /**
             * @brief Set the selected nozzle type for a given index.
             */
            void setSelectedNozzleType(NOZZLE_TYPE val, uint8_t index) { parameters.selectedNozzleType[index] = val; }

            /**
             * @brief Get the dosage value for a given index.
             */
            float getDosageValue(uint8_t index) const { return parameters.dosageValue[index]; }

            /**
             * @brief Set the dosage value for a given index.
             */
            void setDosageValue(float val, uint8_t index) { parameters.dosageValue[index] = val; }
            /**
             * @brief Get the nozzle valve count.
             */
            float getNozzleValveCount() const { return parameters.nozzleValveCount; }
            /**
             * @brief Set the nozzle valve count.
             */
            void setNozzleValveCount(float val) { parameters.nozzleValveCount = val; }
    };

} // namespace App::Domain

#endif // APP_DOMAIN_SETTINGSCOMMON_HPP_