#ifndef FACTION_CREATE_MODEL_HPP
#define FACTION_CREATE_MODEL_HPP

#include <cstdint>
#include <string>

namespace FT
{
    struct FactionCreateModel
    {
        std::string Name;
        uint8_t Force, Cunning, Wealth;
    };
}

#endif
