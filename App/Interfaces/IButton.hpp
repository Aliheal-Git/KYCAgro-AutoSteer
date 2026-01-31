// File: IButtonEventListener.hpp
// Path: app\Interfaces\IButtonEventListener.hpp
// Created by Alican on 2026-01-19

#ifndef APP_INTERFACES_IBUTTONEVENTLISTENER_HPP_
#define APP_INTERFACES_IBUTTONEVENTLISTENER_HPP_

#include "ButtonCommon.hpp"

using namespace App::Domain;

namespace App::Interfaces {    

/**
 * @brief Interface for classes that listen to button events.
 */
class IButtonEventListener {
public:
    virtual ~IButtonEventListener() = default;
    /**
     * @brief Callback method invoked when a button event occurs.
     * @param queueEvent The button event data.
     */
    virtual void onButtonEvent(const ButtonQueueEvent& queueEvent) = 0;
};

/**
 * @brief Interface for classes that can receive button events.
 */
class IButtonEventSink {
public:
    virtual ~IButtonEventSink() = default;
    /**
     * @brief Posts a button event to the event sink.
     * @param queueEvent The button event to post.
     */
    virtual void postButtonEvent(const ButtonQueueEvent& queueEvent) = 0;
};

} // namespace App::Interfaces

#endif // APP_INTERFACES_IBUTTONEVENTLISTENER_HPP_