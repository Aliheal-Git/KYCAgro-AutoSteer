// File: IFlash.hpp
// Path: App\Interfaces\IFlash.hpp
// Created by Alican on 2026-01-24

#ifndef APP_INTERFACES_IFLASH_HPP_
#define APP_INTERFACES_IFLASH_HPP_

#include <cstdint>

namespace App::Interfaces::FlashInterface {

/**
 * @brief Interface for flash memory operations.
 */
class IFlash {
public:
    /**
     * @brief Reads data from the specified flash memory address.
     * @param address The starting address to read from.
     * @param buffer The buffer to store the read data.
     * @param length The number of bytes to read.
     */
    virtual void readData(uint32_t address, uint8_t* buffer, uint32_t length) = 0;

    /**
     * @brief Writes data to the specified flash memory address.
     * @param address The starting address to write to.
     * @param data The data to write.
     * @param length The number of bytes to write.
     */
    virtual void writeData(uint32_t address, const uint8_t* data, uint32_t length) = 0;

    /**
     * @brief Erases the specified sector of flash memory.
     * @param sectorNumber The sector number to erase.
     */
    virtual void eraseSector(uint32_t sectorNumber) = 0;

    /**
     * @brief Disables write protection on the flash memory.
     */
    virtual void disableWriteProtection() = 0;

    /**
     * @brief Enables write protection on the flash memory.
     */
    virtual void enableWriteProtection() = 0;
    virtual ~IFlash() = default;
};

} // namespace App::Interfaces::FlashInterface

#endif // APP_INTERFACES_IFLASH_HPP_