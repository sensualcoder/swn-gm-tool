#ifndef FACTION_HPP
#define FACTION_HPP

#include <cstdint>
#include <map>

namespace FT
{
    // Const items and structs
    const std::map<int, int> RatingHpMap
    {
        {1, 1},
        {2, 2},
        {3, 4},
        {4, 6},
        {5, 9},
        {6, 12},
        {7, 16},
        {8, 20}
    };

    struct FactionCreateModel
    {
        std::string Name;
        uint8_t Force, Cunning, Wealth;
    };

    // Class definition
    class Faction
    {
        public:
            Faction(std::string, uint8_t, uint8_t, uint8_t);
            Faction(std::string, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);
            Faction(const FactionCreateModel&);

        private:
            std::string Name;
            uint8_t Force, Cunning, Wealth;
            uint8_t Income, Treasury;
            uint8_t CurrentHp, MaxHp;
    };

    // Helper methods
    uint8_t CalcHp(uint8_t, uint8_t, uint8_t);
    uint8_t CalcIncome(uint8_t, uint8_t, uint8_t);
}

#endif
