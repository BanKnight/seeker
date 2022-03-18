#ifndef __EVENT_H__
#define __EVENT_H__

#include <functional>

#include "typedefs.h"

namespace seeker
{
    class Event
    {
    public:
        std::string type;
        EventTargetPtr target;

        Event(const EventTargetPtr& target )
        {
            this->target = target;
        }

        virtual ~Event()
        {
            
        }
    };
}


#endif // __EVENT_H__