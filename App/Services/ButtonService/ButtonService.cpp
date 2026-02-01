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
