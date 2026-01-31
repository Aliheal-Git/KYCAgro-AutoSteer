// File: Window.hpp
// Path: app\Drivers\Window\Window.hpp
// Created by Alican on 2026-01-23

#ifndef APP_DRIVERS_WINDOW_WINDOW_HPP_
#define APP_DRIVERS_WINDOW_WINDOW_HPP_

#include "IWindow.hpp"
#include "i2c.h"

using namespace App::Interfaces;

namespace App::Drivers {

class Window : public IWindow {
	private:
		I2C_HandleTypeDef* i2cHandle;
		uint16_t i2cAddress;
		uint8_t rowCount;
		uint8_t columnCount;

		void setCursorPosition(uint8_t row, uint8_t column);
		void sendData(uint8_t data);
		void saveCustomCharacter(const uint8_t* customChar, customCharIndex index);
	public:
		/**
		 * @brief Construct a new Window object
		 * @param i2cHandle Pointer to the I2C handle
		 * @param i2cAddress The I2C address of the LCD
		 * @param rowCount Number of rows in the LCD
		 * @param columnCount Number of columns in the LCD
		 */
		Window(I2C_HandleTypeDef* i2cHandle, uint16_t i2cAddress, uint8_t rowCount, uint8_t columnCount)
			: i2cHandle(i2cHandle), i2cAddress(i2cAddress), rowCount(rowCount), columnCount(columnCount) {}
		void initiliaze();
        void writeCharacter(const char character, uint8_t row, uint8_t column) override;
        void writeString(const char* str, uint8_t row, uint8_t column) override;
        void writeCustomCharacter(customCharIndex index, uint8_t row, uint8_t column) override;
        void sendCommand(DisplayCommands cmd) override;
        void clearWindow() override;
        void clearLine(uint8_t row) override;
        void hideWindow() override;
        void showWindow() override;
        uint8_t getColumnCount() const override;
        uint8_t getRowCount() const override;
};

} // namespace App::Drivers
#endif // APP_DRIVERS_WINDOW_WINDOW_HPP_
