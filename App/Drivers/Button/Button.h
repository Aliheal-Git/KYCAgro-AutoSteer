/*
 * ButtonsGlobal.h
 *
 *  Created on: Aug 24, 2025
 *      Author: alica
 */

#ifndef BUTTON_BUTTONSGLOBAL_H_
#define BUTTON_BUTTONSGLOBAL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "OneButtonC.h"

#ifdef __cplusplus
}
#endif

#include "IButton.hpp"

using namespace App::Interfaces;

namespace App::Drivers {

/**
 * @brief Button driver class.
 */
class Button : public IButton
{
    public:
        Button(ButtonType type, uint64_t pressDurationMs, uint16_t longPressIntervalMs, bool polarity,  
                    GPIO_TypeDef* gpioPort, uint16_t gpioPin, IButtonEventSink& eventSink);
        ~Button();
        void tick() override { OB_Tick(&button); }
    private:
	    OneButton_t button;
        ButtonType type;
        IButtonEventSink& buttonEventSink;


        /**  
         * @brief Static callback entry point for button press event.
         * @param usrData Pointer to the Button instance.
         */
        static void onPressEntryPoint(void* usrData){
            // Placeholder for static callback
            static_cast<Button*>(usrData)->onPress();
        }
          
        /**  
         * @brief Static callback entry point for button release event.
         * @param usrData Pointer to the Button instance.
         */
        static void onReleaseEntryPoint(void* usrData){
            // Placeholder for static callback
            static_cast<Button*>(usrData)->onRelease(); 
        }
        
        /**  
         * @brief Static callback entry point for during long press event.
         * @param usrData Pointer to the Button instance.
         */
        static void onHeldEntryPoint(void* usrData){
            // Placeholder for static callback
            static_cast<Button*>(usrData)->onHeld();
        }

        /**  
         * @brief Static callback entry point for long press release event.
         * @param usrData Pointer to the Button instance.
         */
        static void onHeldReleaseEntryPoint(void* usrData){
            // Placeholder for static callback
            static_cast<Button*>(usrData)->onHeldRelease();
        }

    protected:
        void onPress();
        void onRelease();
        void onHeld();
        void onHeldRelease();   
};

} // namespace App::Drivers
#endif /* BUTTON_BUTTONSGLOBAL_H_ */
