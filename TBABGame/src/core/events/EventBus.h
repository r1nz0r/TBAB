#pragma once
#include <functional>
#include <map>
#include <vector>
#include <memory>
#include "Event.h"

namespace TBAB
{
    /**
     * @typedef EventHandler
     * @brief A type alias for a function that handles an event.
     */
    using EventHandler = std::function<void(const Events::Event&)>;

    /**
     * @class EventBus
     * @brief A static class for a simple event-driven system.
     *
     * This class allows various parts of the game to communicate without direct dependencies.
     * Components can subscribe to events, and others can publish them.
     */
    class EventBus
    {
    public:
        /**
         * @brief Subscribes a handler function to listen for published events.
         * @param handler The handler function to be called when an event is published.
         */
        static void Subscribe(const EventHandler& handler);
        
        /**
         * @brief Publishes an event to all subscribed handlers.
         * @param event The event object to be published.
         */
        static void Publish(const Events::Event& event);

    private:
        static std::vector<EventHandler> _subscribers;
    };
}
