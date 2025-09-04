#pragma once
#include <functional>
#include <map>
#include <vector>
#include <memory>
#include "Event.h"

namespace TBAB
{
    using EventHandler = std::function<void(const Events::Event&)>;

    class EventBus
    {
    public:
        static void Subscribe(const EventHandler& handler);
        static void Publish(const Events::Event& event);

    private:
        static std::vector<EventHandler> _subscribers;
    };
}
