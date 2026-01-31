#include "ButtonService.hpp"
#include "ButtonCommon.hpp"

#include "main.h"

#include "FreeRTOS.h"
#include "task.h"

using namespace App::Drivers;
using namespace App::Services;
/**
 * @brief Constructor for ButtonService class.
 * @details Initializes the button service, creates the button event queue, and starts the button event handler task.
 * 
 */
ButtonService::ButtonService() {
    // Constructor implementation
    // Create queue
    this->buttonQueueHandle = xQueueCreate(QUEUE_LENGTH, ITEM_SIZE);

    // Create Task
    xTaskCreate(
        this->buttonEventHandlerTaskEntryPoint,                // Task function
        "ButtonEventHandlerTask",            // Task name (debug purposes)
        128*5,                   // Stack size (words, not bytes!)
        this,                  // Task parameters
        osPriorityRealtime-2,                   // Task priority
        &buttonTaskHandle      // Task handle
    );

    // To act like switch increase limit of pressDurationMs
    buttons[0] = new Button(MAIN, 0xFFFFFFFFFFFF, 0, false, BUTTON_MAIN_GPIO_Port, BUTTON_MAIN_Pin, *this);
    buttons[1] = new Button(GPS, 0xFFFFFFFFFFFF, 0, false, BUTTON_GPS_GPIO_Port, BUTTON_GPS_Pin, *this);
    buttons[2] = new Button(DOSAGE, 0xFFFFFFFFFFFF, 0, false, BUTTON_MODE_GPIO_Port, BUTTON_MODE_Pin, *this);
    buttons[3] = new Button(PLUS, 1500, 300, false, BUTTON_PLUS_GPIO_Port, BUTTON_PLUS_Pin, *this);
    buttons[4] = new Button(MINUS, 1500, 300, false, BUTTON_MINUS_GPIO_Port, BUTTON_MINUS_Pin, *this);
    buttons[5] = new Button(MENU, 2500, 0, false, BUTTON_MENU_GPIO_Port, BUTTON_MENU_Pin, *this);
    buttons[6] = new Button(PROGRAM, 2500, 0, false, BUTTON_PROGRAM_GPIO_Port, BUTTON_PROGRAM_Pin, *this);
    buttons[7] = new Button(VALVE1, 0xFFFFFFFFFFFF, 0, true, BUTTON_1_GPIO_Port, BUTTON_1_Pin, *this);
    buttons[8] = new Button(VALVE2, 0xFFFFFFFFFFFF, 0, true, BUTTON_2_GPIO_Port, BUTTON_2_Pin, *this);
    buttons[9] = new Button(VALVE3, 0xFFFFFFFFFFFF, 0, true, BUTTON_3_GPIO_Port, BUTTON_3_Pin, *this);
    buttons[10] = new Button(VALVE4, 0xFFFFFFFFFFFF, 0, true, BUTTON_4_GPIO_Port, BUTTON_4_Pin, *this);
    buttons[11] = new Button(VALVE5, 0xFFFFFFFFFFFF, 0, true, BUTTON_5_GPIO_Port, BUTTON_5_Pin, *this);
    buttons[12] = new Button(VALVE6, 0xFFFFFFFFFFFF, 0, true, BUTTON_6_GPIO_Port, BUTTON_6_Pin, *this);
    buttons[13] = new Button(VALVE7, 0xFFFFFFFFFFFF, 0, true, BUTTON_7_GPIO_Port, BUTTON_7_Pin, *this);
    buttons[14] = new Button(VALVE8, 0xFFFFFFFFFFFF, 0, true, BUTTON_8_GPIO_Port, BUTTON_8_Pin, *this);
    
}

/**
 * @brief Destructor for ButtonService class.
 */
ButtonService::~ButtonService() {
        for (auto* b : buttons)
            delete b;
    }

/**
 * @brief Starts the button service task.
 */
void ButtonService::startButtonService()
{
    // Notify the task to start processing
    xTaskNotifyGive(buttonTaskHandle);
}

/**
 * @brief Registers an event listener to receive button events. 
 * @param listener Pointer to the IButtonEventListener to register.
 * @return true if registration is successful, false if listener list is full.
 */
bool ButtonService::registerEventListener(IButtonEventListener* listener)
{
    for (int i = 0; i < LISTENER_COUNT; ++i)
    {
        if (eventListener[i] == nullptr)
        {
            eventListener[i] = listener;
            return true;
        }
    }
    return false; 
}

/**
 * @brief Task function to detect button events.
 */
void ButtonService::buttonEventHandlerTask()
{
    // Block until task start
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    for(;;)
    {
        osDelay(1);
        for (auto* b : buttons)
        {
            if (b != nullptr)
            {
                b->tick();
            }
        }
    }
}

/**
 * @brief Posts a button event to all registered event listeners.
 * @param event The button queue event to post.
 */
void ButtonService::postButtonEvent(const ButtonQueueEvent& event)
{
    for (int i = 0; i < LISTENER_COUNT; ++i)
    {
        if (eventListener[i] != nullptr)
        {
            eventListener[i]->onButtonEvent(event);
        }
    }
}

void ButtonService::registerButton(IButton* button)
{
    for (int i = 0; i < MAX_BUTTON; ++i)
    {
        if (buttons[i] == nullptr)
        {
            buttons[i] = button;
            return;
        }
    }
}
