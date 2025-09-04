#include "EventBus.h"

namespace TBAB
{
    std::vector<EventHandler> EventBus::_subscribers;

    void EventBus::Subscribe(const EventHandler& handler)
    {
        _subscribers.push_back(handler);
    }

    void EventBus::Publish(const Events::Event& event)
    {
        for (const auto& handler : _subscribers)
        {
            handler(event);
        }
    }
}
