#ifndef FACTION_CREATE_MODEL_HPP
#define FACTION_CREATE_MODEL_HPP

#include <cstdint>
#include <string>

namespace SwnGmTool
{
    struct FactionCreateModel
    {
        std::string Name;
        std::string Description;

        uint8_t Force, Cunning, Wealth;
    };
}

#endif
