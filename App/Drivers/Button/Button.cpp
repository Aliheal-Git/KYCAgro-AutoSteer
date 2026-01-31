#include "Button.h"

using namespace App::Drivers::ButtonDriver;

/**
 * @brief Constructor for Button class.
 * @param type Type of the button.
 * @param pressDurationMs Duration in milliseconds to consider a press.
 * @param longPressIntervalMs Interval in milliseconds for long press events.
 * @param polarity Polarity of the button (true for active high, false for active low
 * @param gpioPort GPIO port where the button is connected.
 * @param gpioPin GPIO pin where the button is connected.
 * @param eventSink Reference to the event sink for button events.
 */
Button::Button(ButtonType type, uint64_t pressDurationMs, uint16_t longPressIntervalMs, bool polarity, 
					GPIO_TypeDef* gpioPort, uint16_t gpioPin, IButtonEventSink& buttonEventSink) 
					: type(type), buttonEventSink(buttonEventSink) {
	

	OB_Init(&button);
    OB_Setup(&button, gpioPort, gpioPin, polarity); // Configure the button
	OB_SetPressMs(&button, pressDurationMs);
	OB_SetDebounceMs(&button, 25);

	OB_AttachCallback(&button, OB_EV_PRESS, onPressEntryPoint);
    OB_AttachCallback(&button, OB_EV_CLICK, onReleaseEntryPoint);
	OB_AttachCallback(&button, OB_EV_DURING_LONG_PRESS, onHeldEntryPoint);
	OB_AttachCallback(&button, OB_EV_LONG_PRESS_STOP, onHeldReleaseEntryPoint);
}

Button::~Button() {
	// Destructor implementation (if needed)
}

/**
 * @brief Handler for button press event.
 */
void Button::onPress(){
	// Default implementation (can be overridden)
	const ButtonQueueEvent event = { type, ButtonEventType::PRESSED };
	// Send to queue from a buttonevent
	buttonEventSink.postButtonEvent(event);
} 

/**
 * @brief Handler for button release event.
 */
void Button::onRelease(){
	// Default implementation (can be overridden)
	const ButtonQueueEvent event = { type, ButtonEventType::RELEASED };
	buttonEventSink.postButtonEvent(event);
}

/**
 * @brief Handler for during long press event.
 */
void Button::onHeld(){
	// Default implementation (can be overridden)
	const ButtonQueueEvent event = { type, ButtonEventType::HELD };
	buttonEventSink.postButtonEvent(event);
}

/**
 * @brief Handler for long press release event.
 */
void Button::onHeldRelease(){
	// Default implementation (can be overridden)
	const ButtonQueueEvent event = { type, ButtonEventType::HELD_RELEASED };
	buttonEventSink.postButtonEvent(event);
}


