#ifndef EVENTS_HPP
#define EVENTS_HPP

namespace FT
{
    enum EventType
    {
        // Faction events
        FACTION_DAMAGED,
        FACTION_DESTROYED

        // Asset events

        // Misc events
    };

    struct Event
    {
        EventType Type;
    };
}

#endif
