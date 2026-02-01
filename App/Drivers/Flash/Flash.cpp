#include "Flash.hpp"
#include "stm32g0xx_hal.h"
#include "stm32g0xx_hal_flash.h"
#include <cstdint>

using namespace App::Drivers;

Flash::Flash() {
    // Constructor implementation (if needed)
}

void Flash::readData(uint32_t address, uint8_t* buffer, uint32_t length){
    for (uint32_t i = 0; i < length; i++) {
        buffer[i] = *(__IO uint8_t*)(address + i);
    }
}

void Flash::writeData(uint32_t address, const uint8_t* data, uint32_t length){
    HAL_FLASH_Unlock();

    for (uint32_t i = 0; i < length; i += 8) {
        uint64_t dataBlock = 0;
        for (uint32_t j = 0; j < 8 && (i + j) < length; ++j) {
            dataBlock |= static_cast<uint64_t>(data[i + j]) << (j * 8);
        }
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, address + i, dataBlock);
    }

    HAL_FLASH_Lock();
}

void Flash::eraseSector(uint32_t sectorNumber){
    FLASH_EraseInitTypeDef EraseInitStruct;
    uint32_t PageError = 0;

    if (sectorNumber >= maxSectorNumber) {
        return; // Invalid sector number
    }

    HAL_FLASH_Unlock();

    EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
    EraseInitStruct.Page = sectorNumber;
    EraseInitStruct.NbPages = 1;

    HAL_FLASHEx_Erase(&EraseInitStruct, &PageError);
    HAL_FLASH_Lock();
}

void Flash::disableWriteProtection(){
    FLASH_OBProgramInitTypeDef OBInit;

    HAL_FLASH_Unlock();
    HAL_FLASH_OB_Unlock();

    OBInit.OptionType = OPTIONBYTE_WRP;
    OBInit.WRPArea = OB_WRPAREA_ZONE_A;
    OBInit.RDPLevel = OB_RDP_LEVEL0;
    OBInit.WRPStartOffset = maxSectorNumber-1;        // start page
    OBInit.WRPEndOffset   = 0;        // end page = start page
    HAL_FLASHEx_OBProgram(&OBInit);

    HAL_FLASH_OB_Lock();
    HAL_FLASH_Lock();
}

void Flash::enableWriteProtection(){
    FLASH_OBProgramInitTypeDef OBInit;

    HAL_FLASH_Unlock();
    HAL_FLASH_OB_Unlock();

    OBInit.OptionType = OPTIONBYTE_WRP;
    OBInit.WRPArea = OB_WRPAREA_ZONE_A;
    OBInit.RDPLevel = OB_RDP_LEVEL0;
    OBInit.WRPStartOffset = 0;        // start page
    OBInit.WRPEndOffset   = maxSectorNumber-1;        // end page = start page
    HAL_FLASHEx_OBProgram(&OBInit);

    HAL_FLASH_OB_Lock();
    HAL_FLASH_Lock();
}