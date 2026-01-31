// File: ButtonService.hpp
// Path: app\Button\ButtonService.hpp
// Created by Alican on 2026-01-18

#ifndef APP_BUTTON_BUTTONSERVICE_HPP_
#define APP_BUTTON_BUTTONSERVICE_HPP_

// Queue storage
#define MAX_BUTTON 16
#define QUEUE_LENGTH 16
#define ITEM_SIZE sizeof(ButtonQueueEvent)
#define LISTENER_COUNT 2

#include "Button.h"
#include "IButton.hpp"

#include "cmsis_os.h"

using namespace App::Drivers;
using namespace App::Interfaces;

namespace App::Services {
    
/**
 * @brief ButtonService class handles button initialization and button events.
 */
class ButtonService : public IButtonEventSink {
public:
    ButtonService();
    ~ButtonService();

    void startButtonService();
    bool registerEventListener(IButtonEventListener* listener);

protected:
    void buttonEventHandlerTask();
private:
    QueueHandle_t buttonQueueHandle;
    TaskHandle_t buttonTaskHandle = NULL;
    Button* buttons[MAX_BUTTON]{};

    IButtonEventListener* eventListener[LISTENER_COUNT] = {nullptr, nullptr};

    /**
     * @brief Entry point for the button event handler task.
     */
    static void buttonEventHandlerTaskEntryPoint(void *pvParameters){
        static_cast<ButtonService*>(pvParameters)->buttonEventHandlerTask();
    }

    void postButtonEvent(const ButtonQueueEvent& event) override;
};  

} // namespace app::Services
#endif // APP_BUTTON_BUTTONSERVICE_HPP_