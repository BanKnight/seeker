#pragma once

#include <memory>
#include <functional>

namespace seeker
{
    class Event;
    class EventTarget;
    class Node;

    struct EventOptions
    {
    public:
        bool capture = true;
        bool once = true;
    };

    using EventPtr = std::shared_ptr<Event>;
    using EventTargetPtr = std::shared_ptr<EventTarget>;
    using EventListener = std::function<void(const EventPtr & event)>;
    using NodePtr = std::shared_ptr<Node>;
}
