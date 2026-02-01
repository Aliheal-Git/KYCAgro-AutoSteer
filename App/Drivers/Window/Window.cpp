#include "Window.hpp"
#include "WindowCommon.hpp"

using namespace App::Drivers;
using namespace App::Interfaces;
using namespace App::Domain;

/**
 * @brief Initialize the LCD window
 */
void Window::initiliaze(){
	if (this->i2cHandle != nullptr && this->i2cAddress != 0){
		// Initialize LCD in 8-bit mode, 1 line, 5x8 dots. This is required for some LCDs to properly initialize.
		sendCommand((DisplayCommands::LCD_FUNCTIONSET) | (static_cast<uint8_t>(FunctionSetCommands::LCD_8BITMODE) 
						| static_cast<uint8_t>(FunctionSetCommands::LCD_1LINE) | static_cast<uint8_t>(FunctionSetCommands::LCD_5x8DOTS))); 
		HAL_Delay(5);
		sendCommand(DisplayCommands::LCD_FUNCTIONSET | (static_cast<uint8_t>(FunctionSetCommands::LCD_8BITMODE) 
						| static_cast<uint8_t>(FunctionSetCommands::LCD_1LINE) | static_cast<uint8_t>(FunctionSetCommands::LCD_5x8DOTS))); 
		HAL_Delay(1);
		sendCommand(DisplayCommands::LCD_FUNCTIONSET | (static_cast<uint8_t>(FunctionSetCommands::LCD_8BITMODE) 
						| static_cast<uint8_t>(FunctionSetCommands::LCD_1LINE) | static_cast<uint8_t>(FunctionSetCommands::LCD_5x8DOTS))); 
		HAL_Delay(1);
		// Switch to 4-bit mode
		sendCommand(DisplayCommands::LCD_FUNCTIONSET | (static_cast<uint8_t>(FunctionSetCommands::LCD_4BITMODE) 
						| static_cast<uint8_t>(FunctionSetCommands::LCD_1LINE) | static_cast<uint8_t>(FunctionSetCommands::LCD_5x8DOTS)));
		HAL_Delay(1);
		// Set function to 4-bit mode, 2 lines, 5x8 dots
		sendCommand(DisplayCommands::LCD_FUNCTIONSET | (static_cast<uint8_t>(FunctionSetCommands::LCD_4BITMODE) 
						| static_cast<uint8_t>(FunctionSetCommands::LCD_2LINE) | static_cast<uint8_t>(FunctionSetCommands::LCD_5x8DOTS)));
		HAL_Delay(1);
		// Display OFF, Cursor OFF, Blink OFF
		sendCommand(DisplayCommands::LCD_DISPLAYMODE | static_cast<uint8_t>(DisplayControl::LCD_DISPLAYOFF) 
						| static_cast<uint8_t>(DisplayControl::LCD_CURSOROFF) | static_cast<uint8_t>(DisplayControl::LCD_BLINKOFF));
		HAL_Delay(1);
		// Clear display
		sendCommand(DisplayCommands::LCD_CLEARDISPLAY);
		HAL_Delay(2); // Clear command requires a delay of >1.52ms
		// Entry mode set: Increment cursor, No display shift
		sendCommand(DisplayCommands::LCD_ENTRYMODE | (static_cast<uint8_t>(EntryModeCommands::LCD_MOVERIGHT) 
						| static_cast<uint8_t>(EntryModeCommands::LCD_CURSORMOVE)));
		HAL_Delay(1);
		sendCommand(DisplayCommands::LCD_CURSORSHIFT | (static_cast<uint8_t>(CursorShiftCommands::LCD_CURSORMOVE) 
						| static_cast<uint8_t>(CursorShiftCommands::LCD_MOVERIGHT)));
		HAL_Delay(1);
		sendCommand(DisplayCommands::LCD_RETURNHOME);
		HAL_Delay(2);
		// Display ON, Cursor OFF, Blink OFF
		sendCommand(DisplayCommands::LCD_DISPLAYMODE | static_cast<uint8_t>(DisplayControl::LCD_DISPLAYON) 
						| static_cast<uint8_t>(DisplayControl::LCD_CURSOROFF) | static_cast<uint8_t>(DisplayControl::LCD_BLINKOFF));
		HAL_Delay(1);
		
		// Load custom characters into CGRAM
		for (uint8_t i = 0; i < CUSTOM_CHAR_COUNT; i++)
			saveCustomCharacter(customChars[i], static_cast<customCharIndex>(i));
	}
}

void Window::hideWindow(){
	sendCommand(DisplayCommands::LCD_DISPLAYMODE | static_cast<uint8_t>(DisplayControl::LCD_DISPLAYOFF));
	HAL_Delay(1);
}

void Window::showWindow(){
	sendCommand(DisplayCommands::LCD_DISPLAYMODE | static_cast<uint8_t>(DisplayControl::LCD_DISPLAYON));
	HAL_Delay(1);
}

void Window::clearWindow(){
	sendCommand(DisplayCommands::LCD_CLEARDISPLAY);
	HAL_Delay(2); // Clear command requires a delay of >1.52ms
}

void Window::clearLine(uint8_t row){
	if (row < this->rowCount){
		setCursorPosition(row, 0);
		for (uint8_t i = 0; i < this->columnCount; i++)
			sendData(static_cast<uint8_t>(' '));
	}
}

void Window::sendCommand(DisplayCommands cmd){
	uint8_t commandData[4] = {0};
	commandData[0] = (static_cast<uint8_t>(cmd) & 0xf0) | static_cast<uint8_t>(DisplayControlBits::LCD_NOBACKLIGHT) | static_cast<uint8_t>(DisplayControlBits::ENABLE) | static_cast<uint8_t>(DisplayControlBits::COMMAND);
	commandData[1] = (static_cast<uint8_t>(cmd) & 0xf0) | static_cast<uint8_t>(DisplayControlBits::LCD_NOBACKLIGHT) | static_cast<uint8_t>(DisplayControlBits::DISABLE) | static_cast<uint8_t>(DisplayControlBits::COMMAND);
	commandData[2] = ((static_cast<uint8_t>(cmd) << 4) & 0xf0) | static_cast<uint8_t>(DisplayControlBits::LCD_NOBACKLIGHT) | static_cast<uint8_t>(DisplayControlBits::ENABLE) | static_cast<uint8_t>(DisplayControlBits::COMMAND);
	commandData[3] = ((static_cast<uint8_t>(cmd) << 4) & 0xf0) | static_cast<uint8_t>(DisplayControlBits::LCD_NOBACKLIGHT) | static_cast<uint8_t>(DisplayControlBits::DISABLE) | static_cast<uint8_t>(DisplayControlBits::COMMAND);
	HAL_I2C_Master_Transmit(i2cHandle, i2cAddress, commandData, 4, 100);
}

void Window::writeCharacter(const char character, uint8_t row, uint8_t column){
	setCursorPosition(row, column);
	sendData(static_cast<uint8_t>(character));
}

/**
 * @brief Send data byte to the LCD
 * @param data Data byte to send
 */
void Window::sendData(uint8_t data){
	uint8_t dataBytes[4] = {0};
	dataBytes[0] = (data & 0xf0) | static_cast<uint8_t>(DisplayControlBits::LCD_NOBACKLIGHT) | static_cast<uint8_t>(DisplayControlBits::ENABLE) | static_cast<uint8_t>(DisplayControlBits::DATA);
	dataBytes[1] = (data & 0xf0) | static_cast<uint8_t>(DisplayControlBits::LCD_NOBACKLIGHT) | static_cast<uint8_t>(DisplayControlBits::DISABLE) | static_cast<uint8_t>(DisplayControlBits::DATA);
	dataBytes[2] = ((data << 4) & 0xf0) | static_cast<uint8_t>(DisplayControlBits::LCD_NOBACKLIGHT) | static_cast<uint8_t>(DisplayControlBits::ENABLE) | static_cast<uint8_t>(DisplayControlBits::DATA);
	dataBytes[3] = ((data << 4) & 0xf0) | static_cast<uint8_t>(DisplayControlBits::LCD_NOBACKLIGHT) | static_cast<uint8_t>(DisplayControlBits::DISABLE) | static_cast<uint8_t>(DisplayControlBits::DATA);
	HAL_I2C_Master_Transmit(i2cHandle, i2cAddress, dataBytes, 4, 100);
}

/**
 * @brief Set the cursor position on the LCD
 * @param row The row number
 * @param column The column number
 */
void Window::setCursorPosition(uint8_t row, uint8_t column){
	if (row < this->rowCount && column < this->columnCount){
		uint8_t address = LCD_ROW_OFFSETS[row] + column;
		sendCommand(DisplayCommands::LCD_SETDDRAMADDR | address);
	}
}

/**
 * @brief Save a custom character to CGRAM
 * @param customChar Pointer to the custom character data (8 bytes)
 * @param index The index to save the custom character (0-7)
 */
void Window::saveCustomCharacter(const uint8_t* customChar, customCharIndex index){
	if (static_cast<uint8_t>(index) >= CUSTOM_CHAR_COUNT)
		return;
	sendCommand(DisplayCommands::LCD_SETCGRAMADDR | (static_cast<uint8_t>(index) << 3));
	for (uint8_t i = 0; i < CUSTOM_CHAR_SIZE; i++)
		sendData(customChar[i]);
}

void Window::writeCustomCharacter(customCharIndex index, uint8_t row, uint8_t column){
	if (static_cast<uint8_t>(index) >= CUSTOM_CHAR_COUNT)
		return;
	setCursorPosition(row, column);
	sendData(static_cast<uint8_t>(index));
}

void Window::writeString(const char* str, uint8_t row, uint8_t column){
	setCursorPosition(row, column);
	while (*str){
		sendData(static_cast<uint8_t>(*str++));
	}
}

uint8_t Window::getColumnCount() const {
	return columnCount;
}
uint8_t Window::getRowCount() const {
	return rowCount;
}