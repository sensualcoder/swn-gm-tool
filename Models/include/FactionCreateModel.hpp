#ifndef FACTION_CREATE_MODEL_HPP
#define FACTION_CREATE_MODEL_HPP

#include <cstdint>
#include <string>
#include <vector>

namespace SwnGmTool
{
    struct FactionCreateModel
    {
        std::string Name;
        std::string Description;

        uint8_t Force;
        uint8_t Cunning;
        uint8_t Wealth;

        std::vector<std::string> Tags;
    };
}

#endif