#ifndef FACTION_HPP
#define FACTION_HPP

#include <cstdint>
#include <map>

#include "Events.hpp"

namespace FT
{
    // Forward declarations
    struct Event;
    class Subject;

    // Enums, structs, const values and objects
    struct FactionCreateModel
    {
        std::string Name;
        uint8_t Force, Cunning, Wealth;
    };

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

    // Class definition
    /** Faction
     */
    class Faction
    {
        public:
            Faction(std::string name, uint8_t force, uint8_t cunning, uint8_t wealth);
            Faction(std::string name, uint8_t force, uint8_t cunning, uint8_t wealth, 
                    uint8_t income, uint8_t treasury, uint8_t currentHp, uint8_t maxHp, uint8_t experience);
            Faction(const FactionCreateModel& faction);

            void TakeDamage(uint8_t damage);

        private:
            std::string Name;
            uint8_t Force, Cunning, Wealth;
            uint8_t Income, Treasury;
            uint8_t CurrentHp, MaxHp;
            uint8_t Experience;
    };

    // Helper methods
    uint8_t CalcHp(uint8_t force, uint8_t cunning, uint8_t wealth);
    uint8_t CalcIncome(uint8_t force, uint8_t cunning, uint8_t wealth);
}

#endif
