// File: ButtonCommon.hpp
// Path: app\Domain\ButtonCommon.hpp
// Created by Alican on 2026-01-19

#ifndef APP_DOMAIN_BUTTONCOMMON_HPP_
#define APP_DOMAIN_BUTTONCOMMON_HPP_

namespace App::Domain {

    /**
 * @brief Enumeration of button types.
 * MAIN: Main Valve Switch
 * GPS: GPS Mode S  witch
 * DOSAGE: Dosage Mode Switch
 * PLUS: Increase Value Button
 * MINUS: Decrease Value Button
 * MENU: Menu Page Button
 * PROGRAM: Program Page Button
 * VALVE1: Valve 1 Control Switch
 * VALVE2: Valve 2 Control Switch
 * VALVE3: Valve 3 Control Switch
 * VALVE4: Valve 4 Control Switch
 * VALVE5: Valve 5 Control Switch
 * VALVE6: Valve 6 Control Switch
 * VALVE7: Valve 7 Control Switch
 * VALVE8: Valve 8 Control Switch
 */
 enum class ButtonType {
    MAIN,
    GPS,
    DOSAGE,
    PLUS,
    MINUS,
	MENU,
    PROGRAM,
	VALVE1,
	VALVE2,
	VALVE3,
	VALVE4,
	VALVE5,
    VALVE6,
    VALVE7,
    VALVE8
} ;  

/**
 * @brief Enumeration of button event types.
 * PRESSED: Button Pressed Event
 * RELEASED: Button Released Event
 * HELD: Button Held Down Event
 * HELD_RELEASED: Button Held and then Released Event
 */
 enum class ButtonEventType {
    PRESSED,
    RELEASED,
    HELD,
    HELD_RELEASED,
};

/**
 * @brief Queue event structure for button events.
 */
struct ButtonQueueEvent {
    ButtonType buttonType;            // which button
    ButtonEventType eventType;       // event type
};

} // namespace App::Domain

#endif // APP_DOMAIN_BUTTONCOMMON_HPP_

