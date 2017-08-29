#ifndef FACTION_HPP
#define FACTION_HPP

#include <cstdint>
#include <string>

namespace SwnGmTool
{
    struct Faction
    {
        std::string Name;
        std::string Homeworld;

        uint8_t Might;
        uint8_t Cunning;
        uint8_t Wealth;

        uint8_t FacCreds;

        uint8_t CurrentHP;
        uint8_t MaxHP;
    };
}

#endif
