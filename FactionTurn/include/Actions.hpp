#ifndef ACTIONS_HPP
#define ACTIONS_HPP

#include <string>
#include <vector>

#include "Events.hpp"

namespace FT
{
    enum ActionType
    {
    };

    struct Action
    {
        std::string Name;
        ActionType Type;
        std::vector<Event> Events;
    };
}

#endif
