// File: WindowCommon.hpp
// Path: App\Domain\WindowCommon.hpp
// Created by Alican on 2026-01-23

#ifndef APP_DOMAIN_WINDOWCOMMON_HPP_
#define APP_DOMAIN_WINDOWCOMMON_HPP_

#include <cstdint>
#include <sys/types.h>
#define CUSTOM_CHAR_COUNT 8
#define CUSTOM_CHAR_SIZE 8
namespace App::Domain::WindowCommon {

const uint8_t MAX_ROWS = 4;
const uint8_t MAX_COLUMNS = 20;

/**
 * @brief Indices for custom characters on the LCD
 * heartIndex: Index for heart symbol
 * rightTriangleIndex: Index for right triangle symbol
 * leftTriangleIndex: Index for left triangle symbol
 * rainDropIndex: Index for raindrop symbol
 * rainSpreyIndex: Index for rain spray symbol
 * starIndex: Index for star symbol
 * solidSquareIndex: Index for solid square symbol
 * smileyIndex: Index for smiley face symbol
 */
enum class customCharIndex : uint8_t {
    heartIndex = 0,
    rightTriangleIndex = 1,
    leftTriangleIndex = 2,
    rainDropIndex = 3,
    rainSpreyIndex = 4,
    starIndex = 5,
    solidSquareIndex = 6,
    smileyIndex = 7
};

/**
 * @brief Custom character bitmaps for the LCD
 * 1: Heart symbol
 * 2: Right triangle symbol
 * 3: Left triangle symbol
 * 4: Raindrop symbol
 * 5: Rain spray symbol
 * 6: Star symbol
 * 7: Solid square symbol
 * 8: Smiley face symbol
 */
const uint8_t customChars[CUSTOM_CHAR_COUNT][CUSTOM_CHAR_SIZE] = {
    // Heart symbol
    {
        0b00000,
        0b01010,
        0b11111,
        0b11111,
        0b11111,
        0b01110,
        0b00100,
        0b00000
    },
    // Right triangle symbol
    {
        0b00010,
        0b00110,
        0b01110,
        0b11110,
        0b01110,
        0b00110,
        0b00010,
        0b00000,
    },
    // Left triangle symbol
    {
        0b01000,
        0b01100,
        0b01110,
        0b01111,
        0b01110,
        0b01100,
        0b01000,
        0b00000
    },
    // Raindrop symbol
    {
        0b00000,
        0b10001,
        0b11011,
        0b01110,
        0b10101,
        0b11011,
        0b01110,
        0b00100
    },
    // Rain spray symbol
    {
        0b00100,
        0b01001,
        0b10010,
        0b00100,
        0b01001,
        0b10010,
        0b00100,
        0b01000
    },
    // Star symbol
    {
        0b00100,
        0b10101,
        0b01110,
        0b11111,
        0b01110,
        0b10101,
        0b00100,
        0b00000
    },
    // Solid square symbol
    {
        0b11111,
        0b11111,
        0b11111,
        0b11111,
        0b11111,
        0b11111,
        0b11111,
        0b11111
    },
    // Smiley face symbol
    {
        0b00000,
        0b01010,
        0b00000,
        0b00000,
        0b10001,
        0b01110,
        0b00000,
        0b00000
    }
};

/**
 * @brief Row offsets for the LCD display
 * Used to calculate the starting address of each row
 * 0x00: Offset for row 0
 * 0x40: Offset for row 1
 * 0x14: Offset for row 2
 * 0x54: Offset for row 3
 */
const uint8_t LCD_ROW_OFFSETS[] = {0x00, 0x40, 0x14, 0x54};

/**
 * @brief Command enums for the display
 * LCD_CLEARDISPLAY: Clear display command
 * LCD_RETURNHOME: Return home command
 * LCD_ENTRYMODESET: Entry mode set command. It can be combined with entry mode commands.
 * LCD_DISPLAYCONTROL: Display control command. It can be combined with display control settings.
 * LCD_CURSORSHIFT: Cursor shift command. DB3 = S/C (Screen/Cursor) and DB2 = R/L (Right/Left) DB1 = 0 DB0 = 0 to move the cursor or display.
 * LCD_FUNCTIONSET: Function set command. It can be combined with function set settings.
 * LCD_SETCGRAMADDR: Set CGRAM address command. It can be used for defining custom characters.
 * LCD_SETDDRAMADDR: Set DDRAM address command. It can be used for setting character at cursor position.
 */
enum class DisplayCommands : uint8_t {
    LCD_CLEARDISPLAY = 0x01,
    LCD_RETURNHOME = 0x02,
    LCD_ENTRYMODE = 0x04,
    LCD_DISPLAYMODE = 0x08,
    LCD_CURSORSHIFT = 0x10,
    LCD_FUNCTIONSET = 0x20, 
    LCD_SETCGRAMADDR = 0x40,
    LCD_SETDDRAMADDR = 0x80
};    

inline DisplayCommands operator|(DisplayCommands a, uint8_t b) {
    return static_cast<DisplayCommands>(static_cast<uint8_t>(a) | (b));
}
/**
 * @brief Cursor movement settings for the display
 * LCD_DISPLAYMOVE: Display shift
 * LCD_CURSORMOVE: No display shift
 * LCD_MOVERIGHT: Move right
 * LCD_MOVELEFT: Move left
 */
enum class EntryModeCommands : uint8_t {
    LCD_DISPLAYMOVE = 0x01,
    LCD_CURSORMOVE = 0x00,
    LCD_MOVERIGHT = 0x02,
    LCD_MOVELEFT = 0x00
};

/**
 * @brief Control settings for the display
 * LCD_DISPLAYON: Display on
 * LCD_DISPLAYOFF: Display off
 * LCD_CURSORON: Cursor on
 * LCD_CURSOROFF: Cursor off
 * LCD_BLINKON: Blink on
 * LCD_BLINKOFF: Blink off
 */
enum class DisplayControl : uint8_t {
    LCD_DISPLAYON = 0x04,
    LCD_DISPLAYOFF = 0x00,
    LCD_CURSORON = 0x02,
    LCD_CURSOROFF = 0x00,
    LCD_BLINKON = 0x01,
    LCD_BLINKOFF = 0x00
};

/**
 * @brief Cursor shift settings for the display
 * LCD_DISPLAYMOVE: Enable display move after character write
 * LCD_CURSORMOVE: Enable cursor move after character write
 * LCD_MOVERIGHT: Move to the right
 * LCD_MOVELEFT: Move to the left
 */
enum class CursorShiftCommands : uint8_t {
    LCD_DISPLAYMOVE = 0x08,
    LCD_CURSORMOVE = 0x00,
    LCD_MOVERIGHT = 0x04,
    LCD_MOVELEFT = 0x00
};

/**
 * @brief Function set settings for the display
 * LCD_8BITMODE: 8-bit mode
 * LCD_4BITMODE: 4-bit mode
 * LCD_2LINE: 2-line display
 * LCD_1LINE: 1-line display
 * LCD_5x10DOTS: 5x10 dots character font
 * LCD_5x8DOTS: 5x8 dots character font
 */
enum class FunctionSetCommands : uint8_t {
    LCD_8BITMODE = 0x10,
    LCD_4BITMODE = 0x00,
    LCD_2LINE = 0x08,
    LCD_1LINE = 0x00,
    LCD_5x10DOTS = 0x04,
    LCD_5x8DOTS = 0x00
};

/**
 * @brief Control bits for the display
 * LCD_BACKLIGHT: Backlight on
 * LCD_NOBACKLIGHT: Backlight off
 * ENABLE: Enable bit
 * DISABLE: Disable bit
 * READ: Read bit
 * WRITE: Write bit
 * COMMAND: Command bit
 * DATA: Data bit
 */
enum class DisplayControlBits : uint8_t {
    LCD_BACKLIGHT = 0x08,
    LCD_NOBACKLIGHT = 0x00,
    ENABLE = 0x04,
    DISABLE = 0x00,
    READ = 0x02,
    WRITE = 0x00,
    COMMAND = 0x00,
    DATA = 0x01
};

} // namespace App::Domain::WindowCommon

#endif // APP_DOMAIN_WINDOWCOMMON_HPP_