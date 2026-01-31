// File: Flash.hpp
// Path: App\Drivers\Flash\Flash.hpp
// Created by Alican on 2026-01-24

#ifndef APP_DRIVERS_FLASH_FLASH_HPP_
#define APP_DRIVERS_FLASH_FLASH_HPP_

#include "IFlash.hpp"
#include <cstdint>

using namespace App::Interfaces;

namespace App::Drivers {

/**
 * @brief Flash memory driver class implementing IFlash interface.
 */
class Flash : public IFlash {
    private: 
        const uint32_t maxSectorNumber = 64;
    public:
        Flash();
        void readData(uint32_t address, uint8_t* buffer, uint32_t length) override;
        void writeData(uint32_t address, const uint8_t* data, uint32_t length) override;
        void eraseSector(uint32_t sectorNumber) override;
        void disableWriteProtection() override;
        void enableWriteProtection() override;
};

} // namespace App::Drivers


#endif // APP_DRIVERS_FLASH_FLASH_HPP_