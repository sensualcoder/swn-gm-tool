#ifndef PLANET_TAGS_HPP
#define PLANET_TAGS_HPP

#include <list>
#include <string>

namespace SwnGmTool
{
    struct PlanetTag
    {
        std::string Name;
        std::string Description;
        std::list<std::string> Enemies;
        std::list<std::string> Friends;
        std::list<std::string> Complications;
        std::list<std::string> Things;
        std::list<std::string> Places;
    };

    const std::list<PlanetTag> WorldTags
    {
        {"Abandoned Colony", "", {}, {}, {}, {}, {} }
    };
}

#endif
