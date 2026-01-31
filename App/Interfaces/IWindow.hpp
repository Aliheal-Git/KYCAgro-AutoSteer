// File: IWindow.hpp
// Path: App\Interfaces\IWindow.hpp
// Created by Alican on 2026-01-24

#ifndef APP_INTERFACES_IWINDOW_HPP_
#define APP_INTERFACES_IWINDOW_HPP_

#include "WindowCommon.hpp"

using namespace App::Domain::WindowCommon;

namespace App::Interfaces::WindowInterface {

/**
 * @brief Interface for window display operations.
 */
class IWindow {
    public:
    
        /**
         * @brief Writes a character to the specified position on the window.
         * @param character The character to write.
         * @param row The row position.
         * @param column The column position.
         */
        virtual void writeCharacter(const char character, uint8_t row, uint8_t column) = 0;

        /**
         * @brief Writes a string to the specified position on the window.
         * @param str The string to write.
         * @param row The row position.
         * @param column The column position.
         */
        virtual void writeString(const char* str, uint8_t row, uint8_t column) = 0;

        /**
         * @brief Writes a custom character to the specified position on the window.
         * @param index The index of the custom character.
         * @param row The row position.
         * @param column The column position.
         */
        virtual void writeCustomCharacter(customCharIndex index, uint8_t row, uint8_t column) = 0;

        /**
         * @brief Sends a command to the window display.
         * @param cmd The command to send.
         */
        virtual void sendCommand(DisplayCommands cmd) = 0;

        /**
         * @brief Clears the entire window display.
         */
        virtual void clearWindow() = 0;

        /**
         * @brief Clears a specific line on the window display.
         * @param row The row to clear.
         */
        virtual void clearLine(uint8_t row) = 0;

        /**
         * @brief Hides the window display.
         */
        virtual void hideWindow() = 0;

        /**
         * @brief Shows the window display.
         */
        virtual void showWindow() = 0;
        virtual ~IWindow() = default;
};

} // namespace App::Interfaces::WindowInterface
#endif // APP_INTERFACES_IWINDOW_HPP_