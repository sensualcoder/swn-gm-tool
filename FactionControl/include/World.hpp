#ifndef WORLD_HPP
#define WORLD_HPP

#include <cstdint>
#include <string>

namespace SwnGmTool
{
    struct World
    {
        uint8_t HexID;
        std::string Name;
        uint8_t TechLevel;
    };
}

#endif
