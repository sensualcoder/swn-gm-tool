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

template<>
struct std::hash<SwnGmTool::Faction>
{
    size_t operator()(const SwnGmTool::Faction& f) const
    {
        std::hash<std::string> string_hash;
        return string_hash(f.Name);
    }
};


template<>
struct std::equal_to<SwnGmTool::Faction>
{
    bool operator()(const SwnGmTool::Faction& a, const SwnGmTool::Faction& b) const
    {
        return a.Name == b.Name;
    };
};

#endif
