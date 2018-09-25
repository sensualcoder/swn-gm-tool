#ifndef FACTION_MODEL_HPP
#define FACTION_MODEL_HPP

#include <cstdint>
#include <string>

namespace FT
{
    struct FactionModel
    {
        std::string Name;
        uint8_t Force, Cunning, Wealth;
        uint8_t Income, Treasury;
        uint8_t CurrentHp, MaxHp;
        uint8_t Experience;
    };
}

#endif
