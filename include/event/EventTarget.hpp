#pragma once

#include <memory>

#include "event/Event.hpp"

namespace seeker
{

    class EventTarget
    {
    public:
        EventTarget()
        {

        };
        virtual ~EventTarget()
        {

        };

    public:
        void addEventListener(const std::string & type,const EventListener & listener,const EventOptions & options = EventOptions())
        {

        };
        void addEventListener(const std::string & type,const EventListener & listener,bool useCapture)
        {

        };
        void removeEventListener(const std::string & type,const EventListener & listener)
        {

        }
        void dispatchEvent()
        {

        }
    };
}