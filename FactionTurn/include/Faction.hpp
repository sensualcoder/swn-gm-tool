#ifndef FACTION_HPP
#define FACTION_HPP

#include <cstdint>
#include <map>

#include "Events.hpp"
#include "FactionCreateModel.hpp"
#include "FactionModel.hpp"
#include "Subject.hpp"

namespace FT
{
    // Forward declarations
    struct FactionCreateModel;
    struct FactionModel;
    class Subject;

    // Enums, structs, const values and objects

    // TODO: Make into a configurable object that is loaded in from a file
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

    // Helper methods
    uint8_t CalcHp(uint8_t force, uint8_t cunning, uint8_t wealth);
    uint8_t CalcIncome(uint8_t force, uint8_t cunning, uint8_t wealth);

    // Class definition
    /** Faction
     */
    class Faction : public Subject
    {
        public:
            Faction(const FactionCreateModel& faction);
            Faction(const FactionModel& faction);

            void TakeDamage(uint8_t damage);

        private:
            std::string Name;
            uint8_t Force, Cunning, Wealth;
            uint8_t Income, Treasury;
            uint8_t CurrentHp, MaxHp;
            uint8_t Experience;
    };
}

#endif
